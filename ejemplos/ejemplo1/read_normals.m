function N2 = read_normals(fname)

fp = fopen(fname,'rb');
width = fread(fp,1,'int32=>int32');
height = fread(fp,1,'int32=>int32');
N = fread(fp,width*height*3,'float32=>float32');
N2 = reshape(N,width,height,3);

end