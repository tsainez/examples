%% green.jpg
% load image
img = imread('01.jpg');
fprintf('Load 01.jpg...\n');

% set green channel to zero
fprintf('Set green channel to zero...\n');
img(:,:,2) = 0;

% show image
figure, imshow(img);

% save image
imwrite(img, 'green.jpg');
fprintf('Save green.jpg...\n');

%% gray.jpg
% reload image
img = imread('01.jpg');
fprintf('Load 01.jpg...\n');

% converting from RGB to gray scale 
fprintf('Convert from RGB to gray scale...\n');
%img(:,:,1) = img(:,:,1) * 0.299;
%img(:,:,2) = img(:,:,2) * 0.587;
%img(:,:,3) = img(:,:,3) * 0.114;

R = img(:,:,1) * 0.299;
G = img(:,:,2) * 0.587;
B = img(:,:,3) * 0.114;

img(:,:,1) = R;
img(:,:,2) = G;
img(:,:,3) = B;

% show image
figure, imshow(img);

% save image
imwrite(img, 'gray.jpg');
fprintf('Save gray.jpg...\n');
