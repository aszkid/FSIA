#include <ctime>
#include <chrono>
#include <thread>
#include <random>
#include "neuralNetwork.hpp"
#include "tinyxml2.h"

#ifdef _MSC_VER
	#include "tinyxml2.cpp"
#endif

using std::vector;
using tinyxml2::XMLDocument;
using tinyxml2::XMLNode;
using tinyxml2::XMLError;
using tinyxml2::XMLElement;

typedef std::mt19937 randEng;
typedef std::uniform_int_distribution<> D;

randEng engine(time(NULL));

int int_rand_range(int low, int up)
{
	return D(low, up)(engine);
}

#define XML_FOREACH_NODE(node, parent, nodeName) for(XMLNode* node = parent->FirstChildElement(nodeName); node; node = node->NextSiblingElement(nodeName))

enum key_mode_e {
	MAJOR,
	MINOR
};

struct note_s
{
	enum accidental_e {
		SHARP,
		FLAT,
		NATURAL,
		NONE
	};
	enum type_e {
		SIXTEENTH,
		EIGHTH,
		QUARTER,
		HALF,
		WHOLE
	};
	
	note_s()
		: duration(0), voice(0), p_step('0'), p_octave(0), accidental(accidental_e::NONE), type(type_e::HALF), rest(false)
	{}

	int duration;
	int voice;
	char p_step;
	int p_octave;
	int accidental;
	int type;
	bool rest;
};

const char* accidental_to_text(int accidental)
{
	switch(accidental)
	{
	case note_s::accidental_e::FLAT:
		return "Flat";
	case note_s::accidental_e::SHARP:
		return "Sharp";
	case note_s::accidental_e::NONE:
		return "NONE!";
	default:
		return "Natural";
	}
}
const char* type_to_text(int type)
{
	switch(type)
	{
	case note_s::type_e::EIGHTH:
		return "Eighth";
	case note_s::type_e::HALF:
		return "Half";
	case note_s::type_e::QUARTER:
		return "Quarter";
	case note_s::type_e::WHOLE:
		return "Whole";
	case note_s::type_e::SIXTEENTH:
		return "Sixteenth";
	default:
		return "DUNNO!";
	}
}

#define TYPE_TOTEXT(note) (note.type == note_s::type_e::EIGHTH ? "Eighth" : (note.type == note_s::type_e::HALF ? "Half" : (note.type == note_s::type_e::QUARTER ? "Quarter" : (note.type == note_s::type_e::SIXTEENTH ? "Sixteenth" : "Whole"))))

int main(int argc, char** argv)
{
	XMLDocument doc;
	XMLError e = doc.LoadFile("two_voices_sig.xml");
	if(e != XMLError::XML_SUCCESS)
	{
		LOG("Failed to load file");
		return EXIT_FAILURE;
	}

	XMLNode* score = doc.FirstChildElement("score-partwise");
	XMLNode* part = score->FirstChildElement("part");

	vector<note_s> notes;
	XMLNode* attribs;
	XMLElement* key_e;
	int key_mode = key_mode_e::MAJOR;
	int key_fifths = 0;
	const char key_sharps_a[7] = {'F', 'C', 'G', 'D', 'A', 'E', 'B'};
	const char key_flats_a[7] = {'B', 'D', 'A', 'D', 'G', 'C', 'F'};

	vector<int> times;

	int note_c = 0;
	XML_FOREACH_NODE(measure, part, "measure")
	{
		LOG("Measure " << measure->ToElement()->Attribute("number") << "...");
	
		if(measure->FirstChildElement("attributes") != NULL)
		{
			LOG("Found new attribures in measure " << measure->ToElement()->Attribute("number"));
			attribs = measure->FirstChildElement("attributes");

			key_e = attribs->FirstChildElement("key");
			LOG("Key has " << key_e->FirstChildElement("fifths")->GetText() << " fifth/s in " << key_e->FirstChildElement("mode")->GetText() << " mode");

			std::string key_mode_t = key_e->FirstChildElement("mode")->GetText();
			if(key_mode_t.compare("major") == 0)
				key_mode = key_mode_e::MAJOR;
			else
				key_mode = key_mode_e::MINOR;

			key_e->FirstChildElement("fifths")->QueryIntText(&key_fifths);
		}
	
		XML_FOREACH_NODE(note, measure, "note")
		{
			note_c++;
		
			XMLElement* note_e = note->ToElement();
			bool is_rest = false;
			note_s n;

			XML_FOREACH_NODE(rest, note, "rest")
			{
				is_rest = true;
				break;
			}
			
			note_e->FirstChildElement("duration")->QueryIntText(&n.duration);
			note_e->FirstChildElement("voice")->QueryIntText(&n.voice);
			
			if(is_rest)
			{			
				n.duration *= 2;
				LOG("Rest (" << n.duration << ") in voice " << n.voice << "...");
				n.rest = true;
			}
			else
			{
				XMLElement* pitch_e = note->FirstChildElement("pitch");
				XMLElement* accid_e = note->FirstChildElement("accidental");
				XMLElement* type_e = note->FirstChildElement("type");

				if(accid_e != NULL)
				{
					std::string accid_t = accid_e->GetText();

					if(accid_t.compare("natural") == 0)
						n.accidental = note_s::accidental_e::NATURAL;
					else if(accid_t.compare("sharp") == 0)
						n.accidental = note_s::accidental_e::SHARP;
					else if(accid_t.compare("flat") == 0)
						n.accidental = note_s::accidental_e::FLAT;
				}
			
				n.p_step = pitch_e->FirstChildElement("step")->GetText()[0];

				for(int key_i = 0; key_i < key_fifths; key_i++)
				{
					if(key_mode == key_mode_e::MAJOR)
					{
						if(n.p_step == key_sharps_a[key_i] && n.accidental != note_s::accidental_e::NATURAL)
							n.accidental = note_s::accidental_e::SHARP;
					}
					else if(key_mode == key_mode_e::MINOR)
					{
						if(n.p_step == key_flats_a[key_i] && n.accidental != note_s::accidental_e::NATURAL)
							n.accidental = note_s::accidental_e::FLAT;
					}
				}

				if(n.accidental == note_s::accidental_e::NONE)
					n.accidental = note_s::accidental_e::NATURAL;

				std::string type_t = type_e->GetText();

				if(type_t.compare("half") == 0)
					n.type = note_s::type_e::HALF;
				else if(type_t.compare("quarter") == 0)
					n.type = note_s::type_e::QUARTER;
				else if(type_t.compare("eighth") == 0)
					n.type = note_s::type_e::EIGHTH;
				else if(type_t.compare("whole") == 0)
					n.type = note_s::type_e::WHOLE;
				else if(type_t.compare("16th") == 0)
					n.type = note_s::type_e::SIXTEENTH;

				pitch_e->FirstChildElement("octave")->QueryIntText(&n.p_octave);
				
				LOG(n.p_step << "-" << accidental_to_text(n.accidental) << " " << type_to_text(n.type) << " (" << n.duration << ") at octave " << n.p_octave << " in voice " << n.voice << "...");
				
			}
			
			if(times.size() < n.voice)
			{
				while(times.size() < n.voice)
					times.push_back(0);
			}
			
			times[n.voice-1] += n.duration;
			
			notes.push_back(n);
		}
	}
	
	for(int& t : times)
		LOG(t);
	
	
	

	/*for(int time_i = 0; time_i != -1; time_i++)
	{
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();



		// work
		//std::this_thread::sleep_for(std::chrono::milliseconds(RAND_RANGE(476, 528)));
		// end work

		std::chrono::high_resolution_clock::duration spent = std::chrono::high_resolution_clock::now() - start;
		uint todo = 1000 - std::chrono::duration_cast<std::chrono::milliseconds>(spent).count();
		if(todo > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(todo));
		std::chrono::high_resolution_clock::duration spent_final = std::chrono::high_resolution_clock::now() - start;
	}*/

	neuralNetwork n(3, 3, 1);

	return EXIT_SUCCESS;
}

