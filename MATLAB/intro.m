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
    
    % if [conditional expression]
    %     ...
    % elseif [conditional expression] 
    %     ...
    % else
    %     ... 
    % end

    % While Loops
    % while [conditional expression] 
    %    ...
    % end
    
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

%% Functions
    f=@(x) x^2+15;
    g=@(x,y) x^3+2*y^2+y/3;

    % General Syntax
    % function [outputs]=myfun(inputs) 
    %   ...
    % end

    function y = coolFunction(x)
        %This function computes the following piecewise function
            %y=x+1if x<=-1
            % =x^2 if -1 < x < = 0 
            % =-x^2 if 0 <= x < 1 
            %=x-1if x>=1

        xLen=length(x);
        y=zeros(0,xLen);    % Create empty vector of length x for i=1:xLen 
                            % Given x, compute the function
        if x(i) <= -1
            y(i) = x(i)+1;
        elseif x(i) > -1 && x(i) < 0
            y(i) = (x(i))^2;
        elseif x(i) > 0 && x(i) < 1 
            y(i) = -(x(i))^2;
        elseif x(i) >= 1
            y(i) = x(i)-1; 
        end
    end
    
    % Plot the function in the range -2 < x < 2
    x = linspace(-2,2); 
    y = coolFunction(x); 
    plot(x,y)