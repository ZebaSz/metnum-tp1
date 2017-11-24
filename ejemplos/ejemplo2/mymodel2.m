function mymodel2()
  x=dlmread('gato_small_x.csv'); N=x;
  y=dlmread('gato_small_y.csv'); N(:,:,2)=y;
  z=dlmread('gato_small_z.csv'); N(:,:,3)=z;
  [height,width,~] = size(N);

  M = sparse(2*height*width, height*width);
  v = zeros(2*height*width,1);
  dicc = zeros(height,width);
  p = 1;
  q = 1;

  for y = 1:height
    for x = 1:width
      dicc(y,x) = q;
      q = q+1;
    end
  end

  for y = 1:height-1
    for x = 1:width-1
      nx = N(y,x,1);
      ny = N(y,x,2);
      nz = N(y,x,3);

      q = dicc(y,x);
      M(p,q) = -nz;
      M(p+1,q) = -nz;

      v(p) = -nx;
      v(p+1) = -ny;

      q = dicc(y,x+1);
      M(p,q) = nz;

      q = dicc(y+1,x);
      M(p+1,q) = nz;

      p = p+2;
    end
  end

  Z = M\v;

  sol = zeros(height,width);

  for y = 1:height-1
    for x = 1:width-1
      nz = N(y,x,3);
      if (nz <= 0.1 && nz >= -0.1)
        sol(y,x) = 0;
      else
        q = dicc(y,x);
        sol(y,x) = Z(q);
      end
    end
  end

  [X,Y] = meshgrid(1:width,1:height);
  figure,surf(X,Y,sol);
  figure,mesh(X,Y,sol);
end

