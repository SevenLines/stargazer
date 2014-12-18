SELECT -sin(RA*0.26) * cos(Dec/180*PI()) as x, -sin(Dec/180*PI()) as y, mag, id
FROM (
    SELECT  RA-{centerRA} as RA,
            case
                when dec-{centerDec} < -90 then dec-{centerDec} + 90
                else dec-{centerDec}
            end as Dec,
            Mag as mag,
            id
    FROM Stars
    WHERE abs(RA-{centerRA}) < 6 or abs(RA-{centerRA}) > 18
)

