SELECT t1.x as x1, t1.y as y1, t2.x as x2, t2.y as y2
FROM edges e
JOIN ({projection_script}) t1 ON t1.id = e.star_id1
JOIN ({projection_script}) t2 ON t2.id = e.star_id2
