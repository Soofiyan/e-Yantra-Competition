/*
*Function Name : node_found_color_2
*Input : None
*Output : None
*Logic : This function will traverse the next node to deposit the nuts in the rack.
*Example Call: node_found_color_2()
*/

void node_found_color_2(){
	stop();
	node_timer = 0; //indicates recent node detection
	current_node = *(p+traversed);//destination reached
	prev_node = *(p+traversed-1);
	if (current_node != final_destination)
	{
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
*Function Name : node_found_deposit_2
*Input : None
*Output : None
*Logic : This function will traverse the next node to deposit the nuts present in the rack to the deposit zones.
*Example Call: node_found_deposit_2()
*/
void node_found_deposit_2(){
	stop();
	node_timer = 0; //indicates recent node detection
	current_node = *(p+traversed);//destination reached
	prev_node = *(p+traversed-1);
	if (current_node == 36)
	{
		stop();
		_delay_ms(3000);
	}
	if (current_node == final_destination)
	{
		stop();
		if (final_destination == 10){
			pick_rack(3);
		}
		else if (final_destination == 37){
			pick_rack(2);
		}
		else if (final_destination == 39){
			pick_rack(1);
		}
		place(prev_node,current_node);
		if (rack[2] == 1)
		final_destination = 10;
		else if (rack[3] == 1)
		final_destination = 37;
		else if(rack[1] == 1)
		final_destination = 39;
		else
		total_done = 1;
		
		if (total_done != 1)
		{
			traversed = 2;
			p = dijsktra1(current_node,final_destination);
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



void check_rack_place_again(int colours){
	if (colours == 1)
	{
		if (rack[2] == 0)
		{
			pickup(prev_node,current_node);
			place_rack(2);
			rack[2] = 1;
		}
		else							//since there may be multiple of one color instead of third color
		{
			for (int i = 1;i<=3;i++)
			{
				if (rack[i] == 0)
				{
					pickup(prev_node,current_node);
					place_rack(i);
					rack[i] = 1;
					break;
				}
			}
		}
	}
	else if (colours == 3)
	{
		for (int i = 1;i<=2;i++)
		{
			if (rack[i] == 0)
			{
				pickup(prev_node,current_node);
				place_rack(i);
				rack[i] = 1;
				break;
			}
		}
	}
}

/*
*Function Name : check_nut_left
*Input : None
*Output : None
*Logic : This function will check that if the nut is present at any other remaining positions so traverse the next node.
*Example Call: check_nut_left()
*/
void check_nut_left(){
	for (int i = 0;i<=5;i++)
	{
		if (nut_status[i] == 1)
		{
			switch(i){
				case 0:final_destination = 17;
				p = dijsktra1(current_node, final_destination);
				traversed = 2;
				destination = *(p+traversed);
				counters = directions(prev_node,current_node,destination);
				turn(counters);
				stop();
				if (obstacle_check() == 1)
				{
					obstacle_found();
				}
				while(current_node != final_destination){
					line_follow();
				}
				stop();
				check_rack_place_again(nuts[i]);
				break;
				case 1:final_destination = 18;
				p = dijsktra1(current_node, final_destination);
				traversed = 2;
				destination = *(p+traversed);
				counters = directions(prev_node,current_node,destination);
				turn(counters);
				stop();
				if (obstacle_check() == 1)
				{
					obstacle_found();
				}
				while(current_node != final_destination){
					line_follow();
				}
				stop();
				check_rack_place_again(nuts[i]);
				break;
				case 2:final_destination = 19;
				p = dijsktra1(current_node, final_destination);
				traversed = 2;
				destination = *(p+traversed);
				counters = directions(prev_node,current_node,destination);
				turn(counters);
				stop();
				if (obstacle_check() == 1)
				{
					obstacle_found();
				}
				while(current_node != final_destination){
					line_follow();
				}
				stop();
				check_rack_place_again(nuts[i]);
				break;
				case 3:final_destination = 21;
				p = dijsktra1(current_node, final_destination);
				traversed = 2;
				destination = *(p+traversed);
				counters = directions(prev_node,current_node,destination);
				turn(counters);
				stop();
				if (obstacle_check() == 1)
				{
					obstacle_found();
				}
				while(current_node != final_destination){
					line_follow();
				}
				stop();
				check_rack_place_again(nuts[i]);
				break;
				case 4:final_destination = 22;
				p = dijsktra1(current_node, final_destination);
				traversed = 2;
				destination = *(p+traversed);
				counters = directions(prev_node,current_node,destination);
				turn(counters);
				stop();
				if (obstacle_check() == 1)
				{
					obstacle_found();
				}
				while(current_node != final_destination){
					line_follow();
				}
				stop();
				check_rack_place_again(nuts[i]);
				break;
				case 5:final_destination = 23;
				p = dijsktra1(current_node, final_destination);
				traversed = 2;
				destination = *(p+traversed);
				counters = directions(prev_node,current_node,destination);
				turn(counters);
				while(current_node != final_destination){
					line_follow();
				}
				stop();
				if (obstacle_check() == 1)
				{
					obstacle_found();
				}
				stop();
				check_rack_place_again(nuts[i]);
				break;
			}
		}
	}
	all_nuts_picked = 1;
}

/*
*Function Name : deposit_2
*Input : None
*Output : None
*Logic : This function will deposit the nuts at the respective deposit zones and will update the rack array accordingly.
*Example Call: deposit_2()
*/
void deposit_2(){
	stop();
	check_nut_left();
	
	if (rack[2] == 1)
	final_destination = 10;
	else if (rack[3] == 1)
	final_destination = 37;
	else if(rack[1] == 1)
	final_destination = 39;
	else
	total_done = 1;
	
	if (total_done != 1)
	{
		p = dijsktra1(current_node, final_destination);
		traversed = 2;
		destination = *(p+traversed);
		counters = directions(prev_node,current_node,destination);
		turn(counters);
		stop();
		if (obstacle_check() == 1)
		{
			obstacle_found();
		}
	}
	
	while (total_done == 0)
	{
		line_follow();
	}
}