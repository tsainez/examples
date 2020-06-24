%% Golden Ratio Approximation
% Initialize a vector to hold the Fibonacci numbers
F = zeros(10,1)

% Input the first two Fibonacci numbers 
F(1) = 1; 
F(2) = 1;

% The following loop uses a recursive relation to calculate the
% reamining 8 Fibonacci numbers we need to find.
for i = 3:10
    F(i) = F(i-1) + F(i-2);
end

% Here we create a function handle for
% the fact that the golden ratio is approximated 
% by computing the ratio of successive Fibonacci 
% numbers given as... 
ri = @(Fi, Fim1) Fi/Fim1; 

% Initialize a vector to hold the ratios for
% the Fibonacci numbers.
r = zeros(10, 1);

% Given
r(1) = 1;

% Computing the ratios using a for loop
for i = 2:10
    r(i) = ri(F(i), F(i-1));
end

x = linspace(1, 10, 10);

plot(x, r, 'LineWidth', 3)
hold on

plot (x, r(length(r)), 'r*', 'LineWidth', 2)

ylim([0.6, 2.3])
hold off
