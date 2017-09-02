function show_normals()

%% 
fname = 'buda.normals.dat';
N2 = read_normals(fname);

fname = 'buda.depths.dat';
Z2 = read_depths(fname);

figure
quiver3(Z2, N2(:,:,1),N2(:,:,2),N2(:,:,3))

fclose(fp);
end
