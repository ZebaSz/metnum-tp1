function map2rgb(N)

%%
N2 = (N - min(N(:)))/ (max(N(:)) - min(N(:)));

rgb = uint8(255*N2);

figure
imshow(rgb)

rgb2 = rgb;
rgb2(:,:,3) = rgb(:,:,1);
rgb2(:,:,1) = rgb(:,:,3);

figure
imshow(rgb2)

end