objs = 3; % set the number of objectives
divs = 12; % how many divisions you want in each coordinate
points = []; % use to save all the sampled points
p = zeros(1, objs); % temporary vector

uniform_generate(p, objs, divs, divs, 0);
scatter3(points(:,1), points(:,2), points(:,3), 'LineWidth', 2);
grid;