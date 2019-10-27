/*
*Function Name : node_found_deposit_1
*Input : None
*Output : None
*Logic : This function will deposit all the nuts for 1st set of nuts which are in the rack.
*Example Call: node_found_deposit_1()
*/
void node_found_deposit_1(){
	stop();
	node_timer = 0; //indicates recent node detection
	current_node = *(p+traversed);//destination reached
	prev_node = *(p+traversed-1);
	if (current_node == final_destination)
	{
		stop();
		if (final_destination == 12){
			pick_rack(3);
		}
		else if (final_destination == 9){
			pick_rack(2);
		}
		else if (final_destination == 7){
			pick_rack(1);
		}
		place(prev_node,current_node);
		if (rack[3] == 1)
		final_destination = 12;
		else if (rack[2] == 1)
		final_destination = 9;
		else if(rack[1] == 1)
		final_destination = 7;
		else
		deposits = 1;
		if (deposits != 1){
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
/*
*Function Name : node_found_deposit_1
*Input : None
*Output : None
*Logic : This function will deposit all the nuts and then will traverse to next node with shortest distance.
*Example Call: node_found_deposit_1()
*/
void deposit_1(){
	if (rack[3] == 1)
	final_destination = 12;
	else if (rack[2] == 1)
	final_destination = 9;
	else if(rack[1] == 1)
	final_destination = 7;
	else
	deposits = 1;

	if (deposits != 1)
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
		base_pwm  = 220;
		kp = 250;
		ki = 0;
		kd  = 250;
	}
	while (deposits == 0)
	{
		line_follow();
	}
}