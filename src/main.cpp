#include <iostream>
#include <fstream>
#include "utils.h"
#include "reconstruct3d.h"

#define SAVE_NORMAL true

#define IMG_0 0
#define IMG_1 4
#define IMG_2 10

struct args {
    bool valid;
    char* ref_fname = nullptr;
    char* fig_fname = nullptr;
    char* lights_fname = nullptr;
};

std::vector<matrix<double>> loadGrayImages(const std::vector<std::string>& files) {
    std::vector<matrix<double>> res;
    for (auto& file : files) {
        res.push_back(Utils::loadGrayImage(file));
    }
    return res;
}

void printUsage() {
    std::cerr <<
            "Uso: ./procesar -r <lista_referencia.txt> -f <lista_figura.txt>\n"
            "\n"
            "Ejemplo: ./procesar -r mate.txt -f caballo.txt\n"
            "\n"
            "(el archivo lista_referencia.txt debe listar\n"
            "las imágenes de la esfera para usar al calibrar)\n"
            "\n"
            "Opciones disponibles:\n"
            " -r - lista de figuras de calibración\n"
            " -f - lista de figuras a procesar\n"
            " -l - lista de luces pre-computadas\n"
            "\n"
            "Si las luces pre-computadas están disponibles,\n"
            "se utilizan en lugar de las figuras de calibración."
              << std::endl;
}

std::string getSubfolder(const std::string& path) {
    size_t pos = 0;
    while(path.find('/', pos) != std::string::npos) {
        pos = path.find('/', pos) + 1;
    }
    return path.substr(0, pos);
}

std::vector<std::string> getFileNames(const std::string &file, std::string &mask) {
    std::vector<std::string> names;
    std::ifstream list(file);

    std::string folder = getSubfolder(file);
    uint n;
    list >> n;
    for (uint i = 0; i < n; ++i) {
        std::string name;
        list >> name;
        names.push_back(folder + name);
    }
    list >> mask;
    mask = folder + mask;
    return names;
}

std::string getOutputName(const std::string &file) {
    size_t pos = 0;
    while(file.find('/', pos) != std::string::npos) {
        pos = file.find('/', pos) + 1;
    }
    size_t ext = pos;
    while(file.find('.', ext + 1) != std::string::npos) {
        ext = file.find('.', ext + 1);
    }
    return file.substr(pos, ext - pos);
}

args read_args(int argc, char** argv) {
    args res;
    for (int i = 0; i < argc - 1; ++i) {
        std::string arg{argv[i]};
        if(arg == "-l") {
            res.lights_fname = argv[++i];
        } else if(arg == "-r") {
            res.ref_fname = argv[++i];
        } else if(arg == "-f") {
            res.fig_fname = argv[++i];
        }
    }
    res.valid = res.fig_fname != nullptr
                && (res.lights_fname != nullptr || res.ref_fname != nullptr);
    return res;
}

int main(int argc, char** argv) {
    args a = read_args(argc, argv);
    if(!a.valid) {
        printUsage();
        return 1;
    }
    std::vector<direction> calibrations;

    //----CALIBRATION
    if(a.lights_fname != nullptr) {
        std::string lightsName(a.lights_fname);
        std::cout << "Cargando luces de " << lightsName << std::endl;
        calibrations = Calibration::load_lights(lightsName);
    } else {
        std::string referenceName(a.ref_fname);
        std::cout << "Cargando figuras de referencia de la lista " << referenceName << std::endl;
        std::string referenceMaskName;
        std::vector<std::string> referenceFiles = getFileNames(referenceName, referenceMaskName);
        Mask::mask referenceMask = Mask::load_mask(referenceMaskName);
        vector<matrix<double>> references = loadGrayImages(referenceFiles);
        for (auto &ref : references) {
            ref = Mask::apply_mask(ref, referenceMask);
        }
        std::cout << "Calibrando en base a la figura de referencia" << std::endl;
        calibrations = Calibration::calibrate(references, referenceMask);
    }
    //----LOADING
    std::string figureName(a.fig_fname);
    std::cout << "Cargando figuras de la lista " << figureName << std::endl;
    std::string figureMaskName;
    std::vector<std::string> figureFiles = getFileNames(figureName, figureMaskName);
    Mask::mask msk = Mask::load_mask(figureMaskName);
    vector<matrix<double>> imgs = loadGrayImages(figureFiles);
    for(auto& img : imgs) {
        img = Mask::apply_mask(img, msk);
        img = Mask::apply_clip(img, msk);
    }
    //----NORMAL-FIELD
    std::string outputName = getOutputName(figureName);
    std::cout << "Calculando el campo normal de la figura " << outputName << std::endl;
    matrix<row<double>> normal = normalField(
            imgs[IMG_0], imgs[IMG_1], imgs[IMG_2],
            calibrations[IMG_0], calibrations[IMG_1], calibrations[IMG_2]);
#if SAVE_NORMAL
    std::cout << "Guardando el campo normal de la figura " << outputName << std::endl;
    Utils::saveMatrix3dFiles(Mask::restore_clip(normal, msk, {0,0,0}), outputName);
#endif
    //----DEPTH
    std::cout << "Estimando las profundidades de la figura " << outputName << std::endl;
    matrix<double> depth = findDepth(normal);
    depth = Mask::restore_clip(depth, msk);
    depth = Mask::apply_mask(depth, msk);
    std::cout << "Guardando las de la figura " << outputName << std::endl;
    Utils::saveMatrixFile(depth, outputName + ".depth.csv");
    //----END
    return 0;
}
