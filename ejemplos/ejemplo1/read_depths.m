function Z2 = read_depths(fname)

fp = fopen(fname,'rb');
width = fread(fp,1,'int32=>int32');
height = fread(fp,1,'int32=>int32');
Z = fread(fp,width*height,'float32=>float32');
Z2 = reshape(Z,width,height);

end