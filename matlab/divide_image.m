% Tested in MATLAB 6.5

% Usage: divide_image('filename', height, width)
% Divide the 'filename' image into pieces of height and width

function divide_image(filename, A, B)
info = imfinfo(filename);
M = floor(info.Height/A);
N = floor(info.Width/B);
image_file = imread(filename);
figure;
imshow(image_file);
figure;
for i = 0:M-1
    for j = 0:N-1
        small_image = imcrop(image_file, [j*B+1, i*A+1, B-1, A-1]);
        h = subplot(M, N, i*M+j+1);
        subimage(small_image);
        axis off;
        imwrite(small_image, strcat(num2str(i), '_', num2str(j), '.jpg'), 'JPEG');
    end
end
return
