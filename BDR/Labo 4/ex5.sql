use sakila;

set global event_scheduler = ON;

drop event if exists delete_row;
create event delete_row on schedule every 1 minute
on completion preserve
do
	delete from customer_store_log 
		where customer_id in (
			select 
				customer_id 
			from (
				select 
					customer_id 
				from customer_store_log
				group by customer_id
				having count(customer_id) > 1 
					and max(unregister_date) < now() - interval 1 year
			) as tab1
		);