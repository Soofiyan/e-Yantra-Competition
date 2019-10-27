/*
*Function Name : node_found_color
*Input : None
*Output : None
*Logic : This function will scan each node to scan each nut colour and thus glow it's corresponding led
*Example Call: node_found_colour()
*/
void node_found_color(){
	node_timer = 0; //indicates recent node detection
	current_node = *(p+traversed);//destination reached
	prev_node = *(p+traversed-1);
	if (current_node == pickup_zone[pickup_zone_index])
	{
		pickup_zone_index++;
		stop();
		if (pickup_zone_index == total_nuts)
		{
			done = 1;
		}
		else {
			final_destination = pickup_zone[pickup_zone_index];
			traversed = 2;
			p = dijsktra1(current_node,pickup_zone[pickup_zone_index]);
			destination = *(p + traversed);
			counters = directions(prev_node,current_node,destination); //determine turn number
			turn(counters); //carry out the turn
			stop();
			if (obstacle_check() == 1)
			{
				obstacle_found();
			}
			stop();
			prev_node = current_node;
		}
		if (counters != 1)
		{
			velocity(-50,-250);
			_delay_ms(170);
			velocity(-255,-120);
			_delay_ms(120);
			velocity(80,255);
			_delay_ms(160);
			velocity(80,0);
			_delay_ms(50);
			stop();
		}
		if (pickup_zone_index == 1){
			base_pwm  = 150;
			kp = 100;
			ki = 0;
			kd  = 120;
		}
		check_nut();
		nuts[nuts_index] = colour;
		check_rack_place();
		nuts_index++;
		stop();
		forward();
	}
	else{
		traversed++;
		destination = *(p + traversed);
		counters = directions(prev_node,current_node,destination); //determine turn number
		turn(counters); //carry out the turn
		stop();
		if (obstacle_check() == 1)
		{
			obstacle_found();
		}
		stop();
	}
}
/*
*Function Name : check_rack_place
*Input : None
*Output : None
*Logic : This function will check the node number according to which it will update the rack array.
*Example Call: check_rack_place()
*/
void check_rack_place(){
	if (colour == 2)
	{
		for (int i = 1;i<=2;i++)
		{
			if (rack[i] == 0)
			{
				pickup(prev_node,current_node);
				place_rack(i);
				rack[i] = 1;
				nut_status[nuts_index] = 0;
				break;
			}
		}
	}
	else if (colour == 1)
	{
		if (rack[3] == 0)
		{
			pickup(prev_node,current_node);
			place_rack(3);
			rack[3] = 1;
			nut_status[nuts_index] = 0;
		}
	}
}
/*
*Function Name : color_scan
*Input : None
*Output : None
*Logic : This function will find the shortest path by using dijkstra algorithm.
*Example Call: color_scan()
*/
void color_scan(){
	final_destination = pickup_zone[pickup_zone_index];
	p = dijsktra1(prev_node, final_destination);
	while(done == 0){
		line_follow();
	}
}