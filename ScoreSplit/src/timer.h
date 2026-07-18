

struct Timer{
	unsigned int previous;
	unsigned int current;
	unsigned int duration;
	bool is_finished()
	{
		return this->current == 0;
	}
	void tick_timer()
	{
		if(!is_finished())
		{
			this->previous = this->current;
			this->current--;
		}
	}
	void set_timer(unsigned int duration){
		this->current = duration;
		this->previous = duration;
		this->duration = duration;
	}
	void reset()
	{
		set_timer(this->duration);
	}
	
};


void tick_all_timers(Timer timers[], int size);