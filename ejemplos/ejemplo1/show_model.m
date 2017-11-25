function show_model()

%%
fname = 'caballo.depth.csv';

Z = dlmread(fname);

[height,width] = size(Z);

[X,Y] = meshgrid(1:width,1:height);

figure,surf(X,Y,Z);
figure,mesh(X,Y,Z);

end
