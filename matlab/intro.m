%% Matlab Graph

%% Flower Petals
    p1 = 9
    p2 = 9
    
    figure(1)
    
    phi = (sqrt(5)-1) / 2
    
    theta2 = 0:0.01:2*pi;   % Angle
    k = cos(phi);           % Rotation
    rho2 = 5*sin(p2*theta2).*cos(p1*theta2)+k;    %Center distance
    
    polarplot(theta2, rho2,"-b","LineWidth",3,"MarkerFaceColor","w")
    rlim([0 3.5]);

%% For Loops
    sum1 = 0 
    for k=1:9
        sum1 = sum1 + 1;
    end

%% Conditionals
    % >, <, >=, <=, ==
    % &&  logical and
    % ||  logical or
    
    % If Statement
    
    if x > 1
         disp("x is greater than 1")
     elseif y > 1 
         disp ("y is greater than 1")
     else 
         disp("neither x nor y is greater than 1") 
     end

    % While Loops
     while x < 1
        ...
     end
    
    % Fizzbuzz example
    for i = 1:100
        if(mod(i,3) && mod(i,5))
            fprintf('%i\n', i);
        else
            if(~mod(i,3))
                fprintf('fizz');
            end
            if(~mod(i,5))
                fprintf('buzz');
            end
            fprintf('\n');
        end
    end
   
