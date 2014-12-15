-- звезды северного полушария
SELECT id, cos(Dec)*cos(RA) as x, cos(DEC)* cos(RA) as y
FROM stars
WHERE id in (
    SELECT id
    FROM stars
    WHERE DEC > 0)
