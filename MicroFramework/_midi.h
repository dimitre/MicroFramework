
// DOCS
// https://github.com/jcelerier/libremidi/blob/master/docs/usage.md

libremidi::midi_out midiout;

void listMidiPorts() {
	cout << "listMidiPorts" << endl;
	unsigned int nPorts = midiout.get_port_count();
    cout << "nPorts : " << nPorts << endl;
	if (nPorts == 0)
	{
		std::cout << "No output ports available!" << std::endl;
	}
	else {
		for (unsigned int i = 0; i < nPorts; i++) {
			string portName = midiout.get_port_name(i);
			cout << "  Output port #" << i << ": " << portName << endl;
		}
	}
}

void setupMidi() {
	midiout.open_port(0);
}

void sendMidi() {
//    cout << "sendmidi" << endl;
//	delay(.1);
	if (rand() > .01) {
		std::vector<unsigned char> message (3);

		message[0] = 144;
		message[1] = uint8_t(rand() * 100 + 20);
		message[2] = uint8_t(rand() * 64);
		
		midiout.send_message(message);
//		cout << "nota" << endl;
	}
}
