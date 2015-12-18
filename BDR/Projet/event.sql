use domotique;

set global event_scheduler = ON;

drop event if exists event_hist_deplacement;
create event event_hist_deplacement on schedule every 1 month
on completion preserve
do
	delete from hist_deplacement 
		where date_sortie < now() - interval 1 year
;

drop event if exists event_hist_utilisation;
create event event_hist_utilisation on schedule every 1 month
on completion preserve
do
	delete from hist_utilisation
		where date_fin < now() - interval 1 year
;