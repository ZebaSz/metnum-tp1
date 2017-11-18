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

  for y = 1:height-1
    for x = 1:width-1
      nx = N(y,x,1);
      ny = N(y,x,2);
      nz = N(y,x,3);
      if (nz > 0.001)
        if (y == height-1 || x == width-1)
          M(p,q) = -nz;
          v(q) = -nx;
          dicc(y,x) = q;
          m(p+1,q) = 0;
          dicc(y,x+1) = q;

          m(p,q+1) = -nz;
          v(q+1) = ny;
          m(p+height,q+1) = 0;
          dicc(y+1,x) = q+1;
         else
          m(p,q) = -nz;
          v(q) = nx;
          dicc(y,x) = q;
          m(p+1,q) = nz;
          dicc(y,x+1) = q;

          m(p,q+1) = -nz;
          v(q+1) = ny;
          m(p+height,q+1) = nz;
          dicc(y+1,x) = q+1;
        end
        q = q+2;
      end
      p = p+1;
    end
  end

  Z = M\v;

  sol = zeros(height,width);

  for y = 1:height-1
    for x = 1:width-1
      nz = N(y,x,3);
      if (nz <= 0.001)
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

