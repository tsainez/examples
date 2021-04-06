function [corner_x, corner_y] = Harris_corner_detector...
                                    (I, sigma1, sigma2, alpha, R_threshold, name)
    
	%% Gaussian kernels
    hsize1 = 1 + 2 * ceil(sigma1 * 2);
    hsize2 = 1 + 2 * ceil(sigma2 * 2);

    gaussian_kernel1 = fspecial('gaussian', hsize1, sigma1);
    gaussian_kernel2 = fspecial('gaussian', hsize2, sigma2);
    
    %% derivative filter
    Dx = [1, 0, -1];
    Dy = [1; 0; -1];
    
    %% Use derivative of Gaussian to compute x-gradient (Ix) and y-gradient (Iy)
    Ix = imfilter(I, Dx, 'replicate');  % imfilter(I, Dx), gaussian_kernel1
                                        % Ix, gaussian_kernel1, 'replicate'
    Iy = imfilter(I, Dy, 'replicate');  % imfilter(I, Dy), gaussian_kernel1
                                        % Iy, gaussian_kernel1, 'replicate'

    % figure, imshow(Ix + 0.5);
    % figure, imshow(Iy + 0.5);
    
    imwrite(Ix, [name, '_Ix.png']);
    imwrite(Iy, [name, '_Iy.png']);

    %% compute Ixx, Iyy, Ixy
    Ixx = Ix .* Ix;
    Iyy = Iy .* Iy;
    Ixy = Ix .* Iy;

    %% compute Sxx, Syy, Sxy
    Sxx = imfilter(Ixx, gaussian_kernel2);
    Syy = imfilter(Iyy, gaussian_kernel2);
    Sxy = imfilter(Ixy, gaussian_kernel2);
    
    %% compute corner response from determine and trace
    det_M = (Sxx .* Syy) - (Sxy .* Sxy);
    trace_M = Sxx + Syy;
    R = det_M - alpha * (trace_M .^2); % ((Sxx .* Syy) - (Sxy .* Sxy)) - alpha*((Sxx + Syy).^2)

    % figure, imagesc(R); colormap jet; colorbar; axis image; 
    imwrite(R, [name, '_R.png']);
    
    %% find corner map with R > R_threshold
    corner_map = R > R_threshold;
    
    % figure, imshow(corner_map);
    
    imwrite(corner_map, [name, '_corner_map.png']);

    %% find local maxima of R
    local_maxima = imregionalmax(R);
    
    % figure, imshow(local_maxima)
    
    imwrite(local_maxima, [name, '_local_maxima.png']);

    %% final corner map and corner x, y coordinates
    final_corner_map = corner_map & local_maxima;
    
    % figure, imshow(final_corner_map)
    
    imwrite(final_corner_map, [name, '_final_corner_map.png']);
    
    [corner_y, corner_x] = find(final_corner_map);

end

