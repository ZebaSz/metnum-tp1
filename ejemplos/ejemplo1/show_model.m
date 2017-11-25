function show_model()

%%
fname = 'caballo.depth.csv';

Z = dlmread(fname);

[height,width] = size(Z);

[X,Y] = meshgrid(1:width,1:height);

%%% codigo para subsamplear
p = 2; % paso / modificar para ver más o menos datos

X = X(1:p:end, 1:p:end,:);
Y = Y(1:p:end, 1:p:end,:);
Z = Z(1:p:end, 1:p:end,:);
%%% fin codigo para subsamplear

figure,surf(X,Y,Z);
figure,mesh(X,Y,Z);

end
