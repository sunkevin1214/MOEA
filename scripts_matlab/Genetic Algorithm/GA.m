 function [ solution] = GA( fun_handle, l_limit, u_limit, pop_size, max_gen, run)
% fun_handle ÊÇº¯Êý¾ä±ú
% l_limit, u_limit are the lower and upper limits of the decision variables
% pop_size, the size of population for initializing.
% max_gen, maximum generation
% run, the number of independent runs

if ~exist('pop_size', 'var')
    pop_size = 500;
end
if ~exist('max_gen', 'var')
    max_gen = 200;
end
if ~exist('run', 'var')
    run = 5;
end
% for plot the fitness in each run
is_plot = true;

M = 1;
V = size(l_limit, 2);
solutions_list = zeros(run, V+1);
for counter=1:run
% initialize and assign the fitness
populations = rand(pop_size, V).*repmat(u_limit-l_limit, pop_size, 1) + repmat(l_limit, pop_size, 1);
chromosomes = zeros(pop_size, V+1);
chromosomes(:, 1:V) = populations;
for i = 1:pop_size
    chromosomes(i, end) = fun_handle(M, chromosomes(i, 1:V));
end
    best_record = []; % record the best fitness in each generation
    for gen=1:max_gen
        % to do tournament selection
        pool_size = round(pop_size/2);
        tour = 2;
        parent_chromosome = tournament_selection(chromosomes, pool_size, tour);
        % generate offspring
        offspring_chromosome = ...
                genetic_operator(parent_chromosome, ...
                M, V, 20, 20, l_limit, u_limit, fun_handle, 0.9, 1/V);
        % select the best
        combine_chromosome = [chromosomes; offspring_chromosome];
        combine_fitness = combine_chromosome(:, end);
        [B, I] = sort(combine_fitness);
        chromosomes = combine_chromosome(I(1:pop_size), :);
        best_record = [best_record; B(1)];
        plot(best_record);
        title(['The ', num2str(gen), '/', num2str(max_gen), ' generation, Run ', num2str(counter), '/', num2str(run)]);
        drawnow;
    end
    % find the individuals with the smallest fitness
    [B, I] = min(chromosomes(:,end));
    solutions_list(counter,:) = chromosomes(I,:);
end
solution_fitness = solutions_list(:,end);
[B, I] = min(solution_fitness);
solution = solutions_list(I, :);
end

