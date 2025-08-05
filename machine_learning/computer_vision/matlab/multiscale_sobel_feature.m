function feature = multiscale_sobel_feature(img, scale)

    feature = [];
    
    for i = 1:scale
        [mag, orient] = sobel_feature(img);
        f = orient;
        feature = cat(1, feature, f(:));
        img = imresize(img, 0.5);
    end
end