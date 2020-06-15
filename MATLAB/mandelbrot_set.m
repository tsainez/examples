%% The Mandelbrot Set

s = 800;
k = 400;

x0 = -2;    x1 = 1;
y0 = -1.5;  y1 = 1.5;

% Produce the coordinates of a rectangular grid (x, y)
[x,y] = meshgrid(linspace(x0, x1, s), linspace(y0, y1, s));

c = x + 1i * y;
z = zeros(size(c));
P = zeros(size(c));

for n = 1:k
    z = z.^2 + c;
    P(abs(z) > 2 & P == 0) = n - s;
end

figure,
imagesc(P)
colormap jet
axis square