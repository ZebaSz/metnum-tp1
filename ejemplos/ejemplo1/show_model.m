function show_model()

%%
fnameZ = 'buda.depths.dat';
% fnameN = 'buda.normals.dat';

% N = read_normals(fnameN);
Z = read_depths(fnameZ);

[height,width] = size(Z);

[X,Y] = meshgrid(1:width,1:height);

figure,surf(X,Y,Z);
figure,mesh(X,Y,Z);


end
