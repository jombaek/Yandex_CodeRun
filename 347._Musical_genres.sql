WITH RECURSIVE track_genres AS (
    SELECT
        t.id AS track_id,
        g.id AS genre_id,
        t.name AS track_name,
        g.name AS genre_name,
        g.parent_genre_id
    FROM
        track t
        INNER JOIN track_genre tg ON t.id = tg.track_id
        INNER JOIN genre g ON tg.genre_id = g.id
    UNION ALL
    SELECT
        tg.track_id,
        g.id,
        tg.track_name,
        g.name,
        g.parent_genre_id
    FROM
        track_genres tg
        INNER JOIN genre g ON tg.parent_genre_id = g.id
)
SELECT DISTINCT
    track_id,
    genre_id,
    track_name,
    genre_name
FROM
    track_genres
ORDER BY
    track_id,
    genre_id;
