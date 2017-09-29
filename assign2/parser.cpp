int filenumber = 0;

std::ifstream source;
std::string filename = "myscene.scn";
const char* tmp = filename.c_str();
source.open(tmp);
int input_state=0; //reading file state
for(std::string line; std::getline(source, line);) {
	std::istringstream in(line);
	if(input_state==0){
		std::string rawfile;
		in>>rawfile;
		//read raw file
		std::ifstream raw_source;
		const char* raw_tmp = rawfile.c_str();
		raw_source.open(raw_tmp);
		for(std::string raw_line; std::getline(raw_source, raw_line);) {
        	//input coordinate
			std::istringstream rawin(raw_line);
			float x,y,z;
			rawin >> x >> y >> z;
			st.model[filenumber].pts.push_back(x);
			st.model[filenumber].pts.push_back(y);
			st.model[filenumber].pts.push_back(z);
			st.model[filenumber].centroid.x = (st.model[filenumber].centroid.x*st.model[filenumber].num_vertex + x)/(st.model[filenumber].num_vertex + 1);
			st.model[filenumber].centroid.y = (st.model[filenumber].centroid.y*st.model[filenumber].num_vertex + y)/(st.model[filenumber].num_vertex + 1);
			st.model[filenumber].centroid.z = (st.model[filenumber].centroid.z*st.model[filenumber].num_vertex + z)/(st.model[filenumber].num_vertex + 1);
			st.model[filenumber].num_vertex++;
			//input color value
			float r,g,b;
			rawin >> r >> g >> b;
			st.model[filenumber].color.push_back(r);
			st.model[filenumber].color.push_back(g);
			st.model[filenumber].color.push_back(b);
			//push in VBO
			glBindBuffer(GL_ARRAY_BUFFER,vbo[filenumber]);
			glBufferData (GL_ARRAY_BUFFER, st.model[filenumber].pts.size() * sizeof (float) + st.model[filenumber].color.size() * sizeof (float), NULL, GL_STATIC_DRAW);
			glBufferSubData( GL_ARRAY_BUFFER, 0, st.model[filenumber].pts.size() * sizeof (float), &st.model[filenumber].pts[0] );
			glBufferSubData( GL_ARRAY_BUFFER, st.model[filenumber].pts.size() * sizeof (float),st.model[filenumber].color.size() * sizeof (float), &st.model[filenumber].color[0] );
		}
		input_state=1;
	}
	else if(input_state==1){
		in >> st.model[filenumber].xscale >> st.model[filenumber].yscale >> st.model[filenumber].zscale;
		input_state=2;
	}
	else if(input_state==2){
		in >> st.model[filenumber].xtheta >> st.model[filenumber].ytheta >> st.model[filenumber].ztheta;
		input_state=3;
	}
	else if(input_state==3){
		in >> st.model[filenumber].xtrans >> st.model[filenumber].ytrans >> st.model[filenumber].ztrans;
		filenumber++;
		if(filenumber==3) //all raw files parsed
			input_state=4;
		else //next raw file
			input_state=0;
	}
	else if(input_state==4){
		float x,y,z;
		in >> x >> y >> z;
		st.eye = glm::vec3(x,y,z);
		input_state=5;
	}
	else if(input_state==5){
		float x,y,z;
		in >> x >> y >> z;
		st.lookat_pt = glm::vec3(x,y,z);
		input_state=6;
	}
	else if(input_state==6){
		float x,y,z;
		in >> x >> y >> z;
		st.upvec = glm::vec3(x,y,z);
		input_state=7;
	}
	else if(input_state==7){
		in >> st.L >> st.R >> st.T >> st.B;
		input_state=8;
	}
	else if(input_state==8){
		in >> st.N >> st.F;
		input_state=9;
	}

}