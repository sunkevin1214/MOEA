function [ reference_count, reference_weights ] = niche_assigment(vectors, solutions)
%% for each solution s in solutions, find the vector v to whom s has the smallest perpendicular distance while v is from vectors
% in vectors and solutions, each row denotes one data. vectors is m by n,
% solution is N by n. m and N denotes the number of vectors and solutions,
% respectively.

N = size(solutions, 1);
reference_count = zeros(1, size(vectors, 1)); % record how many references are assiged to the solutions
reference_weights = cell(1, size(vectors,1));
for i = 1:N
    dist = perpendicular(vectors, solutions(i, :));
    [min_v, min_index] = min(dist);
    reference_count(min_index) = reference_count(min_index) + 1;
    if isfield(reference_weights{min_index}, 'solutions')
        reference_weights{min_index}.solutions = [reference_weights{min_index}.solutions i];
    else
        reference_weights{min_index}.solutions = [i];
    end
    if isfield(reference_weights{min_index}, 'dist')
        reference_weights{min_index}.dist = [reference_weights{min_index}.dist min_v];
    else
         reference_weights{min_index}.dist = [min_v];
    end
    
end
end

