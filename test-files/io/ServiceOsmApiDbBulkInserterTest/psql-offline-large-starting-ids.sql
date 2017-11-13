BEGIN TRANSACTION;

SELECT pg_catalog.setval('changesets_id_seq', 4);
SELECT pg_catalog.setval('current_nodes_id_seq', 3000000016);
SELECT pg_catalog.setval('current_ways_id_seq', 3000000008);
SELECT pg_catalog.setval('current_relations_id_seq', 3000000005);

COPY changesets (id, user_id, created_at, min_lat, max_lat, min_lon, max_lon, closed_at, num_changes) FROM stdin;
1	1	2017-11-13 20:58:22.267	0	-9999999	0	-9999999	2017-11-13 20:58:22.267	5
2	1	2017-11-13 20:58:22.267	0	-9999999	0	-9999999	2017-11-13 20:58:22.267	5
3	1	2017-11-13 20:58:22.267	0	-9999999	0	-9999999	2017-11-13 20:58:22.267	5
4	1	2017-11-13 20:58:22.267	0	-9999999	0	-9999999	2017-11-13 20:58:22.267	5
\.

COPY current_nodes (id, latitude, longitude, changeset_id, visible, "timestamp", tile, version) FROM stdin;
3000000003	380500000	-776000000	1	t	2017-11-13 20:58:22.267	1704239955	1
3000000004	380100000	-776500000	1	t	2017-11-13 20:58:22.267	1704239316	1
3000000005	380100000	-775500000	1	t	2017-11-13 20:58:22.267	1704239836	1
3000000006	381000000	-776000000	1	t	2017-11-13 20:58:22.267	1704240727	1
3000000007	380000000	-777000000	1	t	2017-11-13 20:58:22.267	1704233711	1
3000000008	380000000	-775000000	2	t	2017-11-13 20:58:22.267	1704241231	1
3000000009	381000000	-774000000	2	t	2017-11-13 20:58:22.267	1704242807	1
3000000010	380000000	-774000000	2	t	2017-11-13 20:58:22.267	1704241767	1
3000000011	381000000	-773000000	2	t	2017-11-13 20:58:22.267	1704330453	1
3000000012	380000000	-773000000	2	t	2017-11-13 20:58:22.267	1704329413	1
3000000013	381000000	-772000000	3	t	2017-11-13 20:58:22.267	1704330973	1
3000000014	380000000	-772000000	3	t	2017-11-13 20:58:22.267	1704329933	1
3000000015	380000000	-771000000	3	t	2017-11-13 20:58:22.267	1704331493	1
3000000016	380000000	-770000000	3	t	2017-11-13 20:58:22.267	1704332013	1
\.

COPY current_node_tags (node_id, k, v) FROM stdin;
3000000016	building	yes
3000000016	name	n1 - n2
\.

COPY nodes (node_id, latitude, longitude, changeset_id, visible, "timestamp", tile, version, redaction_id) FROM stdin;
3000000003	380500000	-776000000	1	t	2017-11-13 20:58:22.267	1704239955	1	\N
3000000004	380100000	-776500000	1	t	2017-11-13 20:58:22.267	1704239316	1	\N
3000000005	380100000	-775500000	1	t	2017-11-13 20:58:22.267	1704239836	1	\N
3000000006	381000000	-776000000	1	t	2017-11-13 20:58:22.267	1704240727	1	\N
3000000007	380000000	-777000000	1	t	2017-11-13 20:58:22.267	1704233711	1	\N
3000000008	380000000	-775000000	2	t	2017-11-13 20:58:22.267	1704241231	1	\N
3000000009	381000000	-774000000	2	t	2017-11-13 20:58:22.267	1704242807	1	\N
3000000010	380000000	-774000000	2	t	2017-11-13 20:58:22.267	1704241767	1	\N
3000000011	381000000	-773000000	2	t	2017-11-13 20:58:22.267	1704330453	1	\N
3000000012	380000000	-773000000	2	t	2017-11-13 20:58:22.267	1704329413	1	\N
3000000013	381000000	-772000000	3	t	2017-11-13 20:58:22.267	1704330973	1	\N
3000000014	380000000	-772000000	3	t	2017-11-13 20:58:22.267	1704329933	1	\N
3000000015	380000000	-771000000	3	t	2017-11-13 20:58:22.267	1704331493	1	\N
3000000016	380000000	-770000000	3	t	2017-11-13 20:58:22.267	1704332013	1	\N
\.

COPY node_tags (node_id, version, k, v) FROM stdin;
3000000016	1	building	yes
3000000016	1	name	n1 - n2
\.

COPY current_ways (id, changeset_id, "timestamp", visible, version) FROM stdin;
3000000004	3	2017-11-13 20:58:22.267	t	1
3000000005	4	2017-11-13 20:58:22.267	t	1
3000000006	4	2017-11-13 20:58:22.267	t	1
3000000007	4	2017-11-13 20:58:22.267	t	1
3000000008	4	2017-11-13 20:58:22.267	t	1
\.

COPY current_way_nodes (way_id, node_id, sequence_id) FROM stdin;
3000000004	3000000005	1
3000000004	3000000004	2
3000000004	3000000003	3
3000000004	3000000005	4
3000000005	3000000008	1
3000000005	3000000007	2
3000000005	3000000006	3
3000000005	3000000008	4
3000000006	3000000010	1
3000000006	3000000009	2
3000000007	3000000012	1
3000000007	3000000011	2
3000000008	3000000015	1
3000000008	3000000014	2
3000000008	3000000013	3
3000000008	3000000015	4
\.

COPY current_way_tags (way_id, k, v) FROM stdin;
3000000006	name	w3
3000000006	highway	road
3000000007	name	w2
3000000007	highway	track
3000000008	building	yes
3000000008	area	yes
3000000008	name	w1
\.

COPY ways (way_id, changeset_id, "timestamp", version, visible, redaction_id) FROM stdin;
3000000004	3	2017-11-13 20:58:22.267	1	t	\N
3000000005	4	2017-11-13 20:58:22.267	1	t	\N
3000000006	4	2017-11-13 20:58:22.267	1	t	\N
3000000007	4	2017-11-13 20:58:22.267	1	t	\N
3000000008	4	2017-11-13 20:58:22.267	1	t	\N
\.

COPY way_nodes (way_id, node_id, version, sequence_id) FROM stdin;
3000000004	3000000005	1	1
3000000004	3000000004	1	2
3000000004	3000000003	1	3
3000000004	3000000005	1	4
3000000005	3000000008	1	1
3000000005	3000000007	1	2
3000000005	3000000006	1	3
3000000005	3000000008	1	4
3000000006	3000000010	1	1
3000000006	3000000009	1	2
3000000007	3000000012	1	1
3000000007	3000000011	1	2
3000000008	3000000015	1	1
3000000008	3000000014	1	2
3000000008	3000000013	1	3
3000000008	3000000015	1	4
\.

COPY way_tags (way_id, k, v, version) FROM stdin;
3000000006	name	w3	1
3000000006	highway	road	1
3000000007	name	w2	1
3000000007	highway	track	1
3000000008	building	yes	1
3000000008	area	yes	1
3000000008	name	w1	1
\.

COPY current_relations (id, changeset_id, "timestamp", visible, version) FROM stdin;
3000000005	4	2017-11-13 20:58:22.267	t	1
\.

COPY current_relation_members (relation_id, member_type, member_id, member_role, sequence_id) FROM stdin;
3000000005	Way	3000000005	outer	1
3000000005	Way	3000000004	inner	2
\.

COPY current_relation_tags (relation_id, k, v) FROM stdin;
3000000005	building	yes
3000000005	name	r1
\.

COPY relations (relation_id, changeset_id, "timestamp", version, visible, redaction_id) FROM stdin;
3000000005	4	2017-11-13 20:58:22.267	1	t	\N
\.

COPY relation_members (relation_id, member_type, member_id, member_role, version, sequence_id) FROM stdin;
3000000005	Way	3000000005	outer	1	1
3000000005	Way	3000000004	inner	1	2
\.

COPY relation_tags (relation_id, k, v, version) FROM stdin;
3000000005	building	yes	1
3000000005	name	r1	1
\.

COMMIT;