function show_depths()

filename = 'caballo.depth.csv'; % Apuntar al archivo de texto con sus Z
Z = dlmread(filename);

figure
imagesc(Z)
colormap(gray)

end