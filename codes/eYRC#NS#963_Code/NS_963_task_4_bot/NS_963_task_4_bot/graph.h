/*
* Team Id: 963
* Author List: Sorabh,Soofiyan,Shreyas,Pranav.
* Filename: graph.h
* Theme: Nutty squirrel
* Functions: forward_wls(), left_turn_wls(int degrees), right_turn_wls(int degrees), turn(int counter), obstacle_turn(int counter), graphs(), directions(int node_p,int now,int next).
* Global Variables: NONE */
*
/*
*
* Function Name: forward_wls
* Input: void
* Output: void
* Logic: Used if the path between current and next node is straight.
		 Uses white line sensors to go forward, get the bot off the current node and then continue with line follow. 
* Example Call: forward_wls();
*
*/
void forward_wls()
{
	forward();		//Goes forward till off the node
}

/*
*
* Function Name: left_turn_wls
* Input: int degrees
* Output: void
* Logic: First get bot off node and Uses white line sensors to turn left until black line is encountered,  turn depends on degrees to be moved to reach next node.
* Example Call: left_turn_wls(45); //Gets bot off node and Turns left until black line is encountered
*
*/
void left_turn_wls(int degrees)
{
	switch (degrees)
	{
		case 45:
		velocity(255,255);
		_delay_ms(100);
		velocity(0,0);
		left(); //left push
		_delay_ms(50);
		while (ADC_Conversion(2) <= threshold) {
			left();
		}
		stop();
		break;
		case 90:
		velocity(255,255);
		_delay_ms(100);
		velocity(0,0);
		left(); //left push
		_delay_ms(150);
		while (ADC_Conversion(2) <= threshold ) {
			left();
		}
		stop();
		break;
		case 135:
		velocity(255,255);
		_delay_ms(100);
		velocity(0,0);
		left(); //left push
		_delay_ms(300);
		while (ADC_Conversion(2) <= threshold) {
			left();
		}
		stop();
		break;
		case 180:
		velocity(255,255);
		_delay_ms(50);
		velocity(0,0);
		left(); //left push
		_delay_ms(350);
		while (ADC_Conversion(2) <= threshold) {
			left();
		}
		stop();
		break;
		default:
		break;
	}
	stop();
}

/*
*
* Function Name: right_turn_wls
* Input: int degrees
* Output: void
* Logic: First get bot off node and Uses white line sensors to turn right until black line is encountered, turn depends on degrees to be moved to reach next node.
* Example Call: right_turn_wls(45); //Gets bot off node and Turns right until black line is encountered
*
*/
void right_turn_wls(int degrees)
{
	switch (degrees)
	{
		case 45:
		velocity(255,255);
		_delay_ms(100);
		velocity(0,0);
		right(); //right push
		_delay_ms(50);
		while (ADC_Conversion(2) <= threshold) {
			right();
		}
		stop();
		break;
		case 90:
		velocity(255,255);
		_delay_ms(100);
		velocity(0,0);
		right(); //right push
		_delay_ms(200);
		while (ADC_Conversion(2) <= threshold) {
			right();
		}
		stop();
		break;
		case 135:
		velocity(255,255);
		_delay_ms(100);
		velocity(0,0);
		right(); //right push
		_delay_ms(300);
		while (ADC_Conversion(2) <= threshold) {
			right();
		}
		stop();
		break;
		case 180:
		velocity(255,255);
		_delay_ms(50);
		velocity(0,0);
		right(); //right push
		_delay_ms(350);
		while (ADC_Conversion(2) <= threshold) {
			right();
		}
		stop();
		break;
		default:
		break;
	}
	stop();
}


/*
*
* Function Name: turn
* Input: int counter
* Output: void
* Logic: Depending on the counter (depends on path between current and next node) passed to function it decides which turn to take and by how many degrees.
* Example Call: turn(1); //the path between current and next node is straight so calls forward_wls to move it forward
*
*/
void turn(int counter) {
	switch (counter) {
		case 1: forward_wls(); // 1->forward path
		break;
		case 2:	right_turn_wls(45); // 2-> right 45 degree path
		break;
		case 3:	right_turn_wls(90); // 3-> right 90 degree path
		break;
		case 4:	right_turn_wls(135); // 4-> right 135 degree path
		break;
		case 5:	left_turn_wls(45); // 5-> left 45 degree path
		break;
		case 6:	left_turn_wls(90); // 6-> left 90 degree path
		break;
		case 7:left_turn_wls(135); // 7-> left 135 degree path
		break;
		case 8:	right_turn_wls(180); // 8-> right 180 degree path
		break;
		case 9:	left_turn_wls(180); // 9-> right 180 degree path
		break;
		default: break;
	}
}

void obstacle_turn(int counter){
	if (1<counter<5)
	{
		left(); //left push
		_delay_ms(1111);
	}
	else{
		right(); //left push
		_delay_ms(1111);
	}
}

/*
*
* Function Name: directions
* Input: void
* Output: void
* Logic: A value is assigned to decide turn to be taken, depending on previous,current and next node.
* Example Call: directions(); //sets direction array values for appropriate turn based on graph.
*
*/
int directions(int node_p,int now,int next){
	if (node_p == 34){
		direction[4][20] = 1;
		direction[4][3] = 6;
		direction[4][5] = 3;
		direction[4][34]=8;
	}
	else if(node_p == 20){
		direction[4][20] = 8;
		direction[4][3] = 3 ;
		direction[4][5] = 6 ;
		direction[4][34]= 1;
	}
	else if(node_p == 5){
		direction[4][20] = 3;
		direction[4][3] = 1 ;
		direction[4][5] = 8 ;
		direction[4][34]= 6;
	}
	else if(node_p == 3){
		direction[4][20] = 6;
		direction[4][3] = 8 ;
		direction[4][5] = 1 ;
		direction[4][34]= 3;
	}


	if(node_p == 4){
		direction[3][14] = 3;
		direction[3][2] = 1 ;
		direction[3][4] = 8 ;
		
	}
	else if(node_p == 2){
		direction[3][14] = 6;
		direction[3][2] = 8 ;
		direction[3][4] = 1 ;
	}
	else if(node_p == 14){
		direction[3][14] = 8;
		direction[3][2] = 3 ;
		direction[3][4] = 6 ;
	}



	if(node_p == 3){
		direction[2][9] = 3;
		direction[2][35] = 1 ;
		direction[2][3] = 8 ;
		
	}
	else if(node_p == 9){
		direction[2][3] = 6;
		direction[2][35] = 3 ;
		direction[2][9] = 8 ;
	}
	else if(node_p == 35){
		direction[2][3] = 1;
		direction[2][35] = 8 ;
		direction[2][9] = 5 ;
	}



	if(node_p == 2){
		direction[9][2] = 8;
		direction[9][8] = 1 ;
		
	}
	else if(node_p == 8){
		direction[9][2] = 1;
		direction[9][8] = 8 ;
	}




	if(node_p == 9){
		direction[8][13] = 3;
		direction[8][7] = 6 ;
		direction[8][9] = 8 ;
	}
	else if(node_p == 7){
		direction[8][13] = 1;
		direction[8][7] = 8 ;
		direction[8][9] = 3 ;
	}
	else if(node_p == 13){
		direction[8][13] = 8;
		direction[8][7] = 1 ;
		direction[8][9] = 6 ;
	}




	if(node_p == 8){
		direction[13][8] = 8;
		direction[13][17] = 1 ;
		direction[13][14] = 3 ;
	}
	else if(node_p == 17){
		direction[13][17] = 8;
		direction[13][8] = 1 ;
		direction[13][14] = 7 ;
	}
	else if(node_p == 14){
		direction[13][14] = 8;
		direction[13][17] = 4 ;
		direction[13][8] = 5 ;
	}




	if(node_p == 3){
		direction[14][3] = 8;
		direction[14][13] = 5 ;
		direction[14][18] = 2 ;
	}
	else if(node_p == 13){
		direction[14][13] = 8;
		direction[14][3] = 2 ;
		direction[14][18] = 6 ;
	}
	else if(node_p == 18){
		direction[14][3] = 5;
		direction[14][13] = 3 ;
		direction[14][18] = 8 ;
	}




	if(node_p == 8){
		direction[7][8] = 8;
		
	}





	if(node_p == 13){
		direction[17][13] = 8;
		direction[17][18] = 4 ;
		
	}
	else if(node_p == 18){
		direction[17][18] = 8;
		direction[17][13] = 6 ;
	}





	if(node_p == 17){
		direction[18][17] = 8;
		direction[18][19] = 1 ;
		direction[18][14] = 3 ;
		
	}
	else if(node_p == 19){
		direction[18][19] = 8;
		direction[18][17] = 1 ;
		direction[18][14] = 6 ;
	}
	else if(node_p == 14){
		direction[18][14] = 8;
		direction[18][17] = 6 ;
		direction[18][19] = 3 ;
	}




	if(node_p == 18){
		direction[19][18] = 8;
		direction[19][20] = 1 ;
	}
	else if(node_p == 20){
		direction[19][18] = 1;
		direction[19][20] = 8 ;
	}




	if(node_p == 19){
		direction[20][4] = 3;
		direction[20][19] = 8 ;
		direction[20][21]= 1 ;
	}
	else if(node_p == 4){
		direction[20][4] = 8;
		direction[20][19] = 6 ;
		direction[20][21]= 3 ;
	}
	else if(node_p == 21){
		direction[20][4] = 6;
		direction[20][19] = 1 ;
		direction[20][21]= 8 ;
	}



	//RIGHT SIDE




	if(node_p == 4){
		direction[5][15] = 6;
		direction[5][4] = 8 ;
		direction[5][6] = 1 ;
		
	}
	else if(node_p == 15){
		direction[5][15] = 8;
		direction[5][4] = 3 ;
		direction[5][6] = 6 ;
	}
	else if(node_p == 6){
		direction[5][15] = 3;
		direction[5][4] = 1 ;
		direction[5][6] = 8 ;
	}



	if(node_p == 5){
		direction[6][10] = 5;
		direction[6][35] = 1 ;
		direction[6][5] = 8 ;
		
	}
	else if(node_p == 10){
		direction[6][5] = 3;
		direction[6][35] = 6 ;
		direction[6][10] = 8 ;
	}
	else if(node_p == 35){
		direction[6][5] = 1;
		direction[6][35] = 8 ;
		direction[6][10] = 3 ;
	}



	if(node_p == 6){
		direction[10][11] = 1;
		direction[10][6] = 8 ;
		
	}
	else if(node_p == 11){
		direction[10][6] = 1;
		direction[10][11] = 8 ;
	}




	if(node_p == 10){
		direction[11][16] = 6;
		direction[11][12] = 3 ;
		direction[11][10] = 8 ;
	}
	else if(node_p == 12){
		direction[11][16] = 1;
		direction[11][12] = 8 ;
		direction[11][10] = 6 ;
	}
	else if(node_p == 16){
		direction[11][16] = 8;
		direction[11][12] = 1 ;
		direction[11][10] = 3 ;
	}




	if(node_p == 11){
		direction[16][11] = 8;
		direction[16][23] = 1 ;
		direction[16][15] = 5 ;
	}
	else if(node_p == 23){
		direction[16][23] = 8;
		direction[16][11] = 1 ;
		direction[16][15] = 4 ;
	}
	else if(node_p == 15){
		direction[16][15] = 8;
		direction[16][23] = 7 ;
		direction[16][11] = 2 ;
	}




	if(node_p == 5){
		direction[15][5] = 8;
		direction[15][16] = 2 ;
		direction[15][22] = 5 ;
	}
	else if(node_p == 16){
		direction[15][16] = 8;
		direction[15][5] = 5 ;
		direction[15][22] = 3 ;
	}
	else if(node_p == 22){
		direction[15][5] = 2;
		direction[15][16] = 6 ;
		direction[15][22] = 8 ;
	}




	if(node_p == 11){
		direction[12][11] = 8;
		
	}





	if(node_p == 16){
		direction[23][16] = 8;
		direction[23][22] = 6 ;
		
	}
	else if(node_p == 22){
		direction[23][22] = 8;
		direction[23][16] = 3 ;
	}





	if(node_p == 23){
		direction[22][23] = 8;
		direction[22][21] = 1 ;
		direction[22][15] = 6 ;
		
	}
	else if(node_p == 21){
		direction[22][21] = 8;
		direction[22][23] = 1 ;
		direction[22][15] = 3 ;
	}
	else if(node_p == 15){
		direction[22][15] = 8;
		direction[22][23] = 3 ;
		direction[22][21] = 6 ;
	}




	if(node_p == 22){
		direction[21][22] = 8;
		direction[21][20] = 1 ;
	}
	else if(node_p == 20){
		direction[21][22] = 1;
		direction[21][20] = 8 ;
	}




	//LOWER


	if(node_p == 2){
		direction[35][2] = 8;
		direction[35][6] = 1 ;
		direction[35][24] = 3 ;
		
	}
	else if(node_p == 6){
		direction[35][6] = 8;
		direction[35][2] = 1 ;
		direction[35][24] = 6 ;
	}
	else if(node_p == 36){
		direction[24][36] = 8;
		direction[35][6] = 3 ;
		direction[35][2] = 6 ;
	}




	if(node_p == 35){
		direction[24][35] = 8;
		direction[24][36] = 1 ;
	}
	else if(node_p == 38){
		direction[36][35] = 1;
		direction[36][38] = 8 ;
	}


	if(node_p == 24){
		direction[36][24] = 8;
		direction[36][38] = 1 ;
	}


	if(node_p == 37){
		direction[38][37] = 8;
		direction[38][39] = 1 ;
		direction[38][36] = 6 ;
		
	}
	else if(node_p == 39){
		direction[38][39] = 8;
		direction[38][37] = 1 ;
		direction[38][36] = 3 ;
	}
	else if(node_p == 36){
		direction[38][36] = 8;
		direction[38][39] = 6 ;
		direction[38][37] = 3 ;
	}





	if(node_p == 38){
		direction[37][38] = 8;
	}


	if(node_p == 38){
		direction[39][38] = 8;
	}
	return direction[now][next];
}


/*
*
* Function Name: graph
* Input: void
* Output: void
* Logic: Graph of arena as per node numbering
* Example Call: graph() // makes bot follow line depending on position w.r.t line
*/
void graphs() {
	for (int i = 0; i <= nodes; i++) {
		for (int j = 0; j <= nodes; j++) {
			if (i == j)
			graph[i][j] = 0;
			else
			graph[i][j] = 99;
		}
	}
	graph[34][4] = 1;
	graph[4][34] = 1;

	graph[2][3] = 1;
	graph[3][2] = 1;
	graph[2][9] = 1;
	graph[9][2] = 1;
	graph[2][35] = 1;
	graph[35][2] = 1;
	
	graph[6][35] = 1;
	graph[35][6] = 1;

	graph[3][4] = 1;
	graph[4][3] = 1;
	graph[3][14] = 1;
	graph[14][3] = 1;

	graph[4][5] = 1;
	graph[5][4] = 1;
	graph[4][20] = 3;
	graph[20][4] = 3;

	graph[5][15] = 1;
	graph[15][5] = 1;
	graph[5][6] = 1;
	graph[6][5] = 1;

	graph[10][6] = 1;
	graph[6][10] = 1;

	graph[8][7] = 1;
	graph[7][8] = 1;

	graph[8][13] = 1;
	graph[13][8] = 1;
	graph[8][9] = 1;
	graph[9][8] = 1;

	graph[10][11] = 1;
	graph[11][10] = 1;

	graph[12][11] = 1;
	graph[11][12] = 1;
	graph[16][11] = 1;
	graph[11][16] = 1;

	graph[13][17] = 1;
	graph[17][13] = 1;
	graph[13][14] = 1;
	graph[14][13] = 1;

	graph[14][18] = 1;
	graph[18][14] = 1;

	graph[15][16] = 1;
	graph[16][15] = 1;
	graph[15][22] = 1;
	graph[22][15] = 1;

	graph[23][16] = 1;
	graph[16][23] = 1;

	graph[17][18] = 1;
	graph[18][17] = 1;

	graph[18][19] = 1;
	graph[19][18] = 1;

	graph[19][20] = 1;
	graph[20][19] = 1;

	graph[20][21] = 1;
	graph[21][20] = 1;

	graph[21][22] = 1;
	graph[22][21] = 1;

	graph[23][22] = 1;
	graph[22][23] = 1;

	graph[17][28] = 1;
	graph[28][17] = 1;

	graph[18][29] = 1;
	graph[29][18] = 1;

	graph[19][30] = 1;
	graph[30][19] = 1;

	graph[21][31] = 1;
	graph[31][21] = 1;

	graph[22][32] = 1;
	graph[32][22] = 1;

	graph[23][33] = 1;
	graph[33][23] = 1;

	graph[9][25] = 1;
	graph[25][9] = 1;

	graph[10][26] = 1;
	graph[26][10] = 1;

	graph[12][27] = 1;
	graph[27][12] = 1;

	
	graph[24][35] = 1;
	graph[35][24] = 1;
	
	graph[24][36] = 1;
	graph[36][24] = 1;
	
	graph[36][38] = 1;
	graph[38][36] = 1;
	
	graph[37][38] = 1;
	graph[38][37] = 1;
	graph[37][40] = 1;
	graph[40][37] = 1;
	
	graph[39][38] = 1;
	graph[38][39] = 1;
	graph[39][41] = 1;
	graph[41][39] = 1;
}