UPDATE  `lacunastories`.`workflow_states`  SET  `sid` =  '1', `wid` =  '1' 
WHERE  `workflow_states`.`name` = '(creation)';

UPDATE  `lacunastories`.`workflow_states`  SET  `sid` =  '2', `wid` =  '1' 
WHERE  `workflow_states`.`name` = 'draft';

UPDATE  `lacunastories`.`workflow_states`  SET  `sid` =  '3', `wid` =  '1' 
WHERE  `workflow_states`.`name` = 'ready_for_annotation';


UPDATE  `lacunastories`.`workflow_transitions`  SET  `sid` =  '1', `target_sid` =  '2' 
WHERE  `workflow_transitions`.`name` = '1_2';
UPDATE  `lacunastories`.`workflow_transitions`  SET  `sid` =  '1', `target_sid` =  '3'
WHERE  `workflow_transitions`.`name` = '1_3';
UPDATE  `lacunastories`.`workflow_transitions`  SET  `sid` =  '2', `target_sid` =  '2' 
WHERE  `workflow_transitions`.`name` = '2_2';
UPDATE  `lacunastories`.`workflow_transitions`  SET  `sid` =  '2', `target_sid` =  '3' 
WHERE  `workflow_transitions`.`name` = '2_3';
UPDATE  `lacunastories`.`workflow_transitions`  SET  `sid` =  '3', `target_sid` =  '2' 
WHERE  `workflow_transitions`.`name` = '3_2';
UPDATE  `lacunastories`.`workflow_transitions`  SET  `sid` =  '3', `target_sid` =  '3' 
WHERE  `workflow_transitions`.`name` = '3_3';


UPDATE  `lacunastories`.`workflows`  SET  `wid` =  '1';