class microApp {
public:

#include "_basic.h"
	
	struct rectangle {
		glm::vec2 pos;
		glm::vec2 dimensions;
		glm::vec2 pos2;
		
	//	bool inside(glm::vec2 & p) const {
		bool inside(glm::vec2 p)  {
			return (p.x > pos.x && p.x < pos2.x) && (p.y > pos.y && p.y < pos2.y);
		}
		
		void draw() {
			//
			rect(pos, dimensions);
		}
		
		void setPos(glm::vec2 p) {
			pos = p;
			pos2 = pos + dimensions;
		}
		
		rectangle(glm::vec2 p, glm::vec2 d) : pos(p), dimensions(d) {
			pos2 = pos + dimensions;
	//		cout << "new rect" << endl;
	//		cout << pos.x << " : " << pos.y << endl;
	//		cout << dimensions.x << " : " << dimensions.y << endl;
	//		cout << pos2.x << " : " << pos2.y << endl;
		};
		
		friend std::ostream& operator<< (std::ostream &o, const rectangle &r)
		{
			return o << "rectangle " << r.pos.x << ", " << r.pos.y << ", " << r.dimensions.x << ", " << r.dimensions.y << endl;
		}
	};
};


class interface : public microApp {
public:
	map <string, float>		pFloat;
	map <string, bool>		pBool;
	
	struct element {
	public:
		rectangle rect = rectangle(glm::vec2(0,0), glm::vec2(200,20));
		rectangle rect2 = rectangle(glm::vec2(0,0), glm::vec2(200,20));
		glm::vec2 pos;
		color cor = color(255,0,0);
		color cor2 = color(0,0,255);
		element() {}
		element(glm::vec2 p) : pos(p) {
			rect2.setPos(pos);
			rect.setPos(pos);
	//		rect2.pos = rect.pos = pos;
			rect2.dimensions.x = random(0,200);
		}
		void draw() {
			fill(cor);
			rect.draw();
			fill(cor2);
			rect2.draw();
		}
		
		void checkMouse(glm::vec2 mouse) {
			if (rect.inside(mouse)) {
				cor = color(random(0,255), random(0,255), random(0,255));
			}
		}
	};
};
