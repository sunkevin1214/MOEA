function [F, dominating_individuals, dominated_individuals] = assign_front(objs, find_all)
%% assign the individuals to their corresponding front
% objs is the objectives of individuals, N¡¡by d, N is the number of
% individuals, and d is the number of objectives
% in some algorithm, it is not necessary to find all the fronts, but the
% first front. find_all parameter is used for this. this algorithm find the
% first front if find_all is set to false. otherwise true.

% F contains the individuals of each front
% dominating_individuals contains dominated individuals of each individuals
% dominated_individuals contains who dominates each individuals,this is
% spcecial for the fitness computation of SPEA or SPEA2 algorithm

if ~exist('find_all', 'var')
    find_all = false;
end

[m, n]  = size(objs);
front = 1;
F{front} = [];
dominating_individuals = []; 
dominated_number = [];   
dominated_individuals = [];

for i = 1:m
    dominating_individuals{i} = []; % the individuals i dominates
    dominated_number{i} = 0; % the number of individuals who dominates i
    dominated_individuals{i} = []; % the dindividuals who dominates i
    for j = 1:m
        if i ~= j
            number_of_more = 0;
            number_of_equal = 0;
            number_of_less = 0;
            for k = 1:n
                if objs(i, k) < objs(j, k)
                    number_of_less = number_of_less + 1;
                elseif objs(i, k) > objs(j, k)
                    number_of_more = number_of_more + 1;
                else
                    number_of_equal = number_of_equal + 1;
                end
            end
            if number_of_less > 0 && number_of_more == 0
                % i dominates j
                dominating_individuals{i} = [dominating_individuals{i} j];
            elseif number_of_more > 0 && number_of_less == 0
                % i is dominated by j
                dominated_individuals{i} = [dominated_individuals{i} j];
                dominated_number{i} = dominated_number{i} + 1;
            end    
        end
    end
    if dominated_number{i} == 0
        F{front} = [F{front} i];
    end
end

if find_all
    while ~isempty(F{front})
        q = [];
        for i = 1:numel(F{front})
           if ~isempty(dominating_individuals{F{front}(i)})
               for j = 1:numel(dominating_individuals{F{front}(i)})
                   current_individual = dominating_individuals{F{front}(i)}(j);
                   dominated_number{current_individual} = dominated_number{current_individual} - 1;
                   if dominated_number{current_individual} == 0
                       q = [q current_individual];
                   end
               end
           end
        end
        front = front + 1;
        F{front} = q;
    end
    F(front) = [];
end
end