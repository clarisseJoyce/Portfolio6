






/*
* Created  by rbh, 27/02/15
* Modified by nas, 18/12/16
*/

#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>

#include "../headers/xmlparser.h"
#include "../headers/route.h"



namespace GPXP
{
	using std::endl;
	const metres Route::granularity = 20;
	const Position Route::northPole = Position(90, 0, 0);

	std::ostringstream oss; //declaration has been made public to be used by all functions
	string temp, lat, lon, temp2, ele; //declaration has been made public to be used by all functions


	Route::Route(string source, bool isFileName)
	{
		using namespace XML_Parser;

		checkFile(isFileName, source);

		if (!constCheck(source, "gpx")) {
		}//changed

		if (!constCheck(source, "rte")) {
		}//changed

		temp = getElement(source, "rte");
		source = getElementContent(temp);
		if (constCheck(source, "name"))
		{
			temp = getAndEraseElement(source, "name");
			routeName = getElementContent(temp);
			oss << endl << "route name is " << routeName;
		}

		if (!constCheck(source, "rtept")) {
		} //changed

		temp = getAndEraseElement(source, "rtept");
		lat = getElementAttribute(temp, "lat");
		lon = getElementAttribute(temp, "lon");
		temp2 = getElement(temp, "ele");
		ele = getElementContent(temp2);
		string name;

		//temp = getElementContent(temp); 
		//line is the same as the temp declaration above, nothing will be affected if removed

		/*
		chunk of code is already inside the while statement
		for the constructor check
		if (constCheck(temp,"name"))
		{
		temp2 = getElement(temp,"name");
		name = getElementContent(temp2);
		}
		*/

		Position currentPos(lat, lon, ele);
		positions.push_back(currentPos);
		positionNames.push_back(name);
		oss << endl << "start position added: " << currentPos.toString();
		while (constCheck(source, "rtept"))
		{
			temp = getAndEraseElement(source, "rtept");
			lat = getElementAttribute(temp, "lat");
			lon = getElementAttribute(temp, "lon");
			ele = getElementContent(getElement(temp, "ele"));

			//temp = getElementContent(temp);

			if (constCheck(temp, "name"))
			{
				temp2 = getElement(temp, "name");
				name = getElementContent(temp2);
			}
			else
			{
				name = "";
			}
			Position nextPos(lat, lon, ele);
			if (distanceBetween(currentPos, nextPos) < granularity)
			{
				oss << endl << "position ignored: " << nextPos.toString();
			}
			else
			{
				positions.push_back(nextPos);
				positionNames.push_back(name);
				oss << endl << "position added: " << nextPos.toString();
				currentPos = nextPos;
			}
		}
		oss << endl << positions.size() << " positions added";
		distCalc();
		constStat(true);
		return;
	}

	bool Route::builtOk() const
	{
		return constructorSucceeded;
	}

	string Route::buildReport() const
	{
		/* Returns the report generated by the constructor, for debugging purposes.
		*/
		implementation(true);
		return constructorReport;
	}

	string Route::name() const
	{
		/* Returns the name of the Route, or "Unnamed Route" if nameless.
		*/
		implementation(false);
		return routeName.empty() ? "Unnamed Route" : routeName;
	}

	metres Route::totalLength() const
	{
		/* Computes and returns the total length of the Route; this is
		* the sum of the distances between the successive Positions of the Route.
		*/
		implementation(false);
		return routeLength;
	}

	metres Route::netLength() const
	{
		/* Returns the distance between the first and last points on the Route.
		*/
		implementation(false);

		const Position & start = positions.front();
		const Position & finish = positions.back();

		metres deltaH = distanceBetween(start, finish);
		metres deltaV = start.getElevation() - finish.getElevation();

		return std::sqrt(std::pow(deltaH, 2) + std::pow(deltaV, 2));
	}

	metres Route::totalHeightGain() const
	{
		/* Returns the sum of all the positive (>0) height differences between points.
		*/
		implementation(false);
		return (0);
	}

	metres Route::netHeightGain() const
	{
		/* Returns the difference in elevation between the first and last points on the
		* Route.
		* Should be negative if there was a net height loss.
		*/
		implementation(false);
		return (0);
	}

	degrees Route::maxUphillGradient() const
	{
		/* Returns the maximum value of gradient between successive points on the Route.
		*/
		implementation(false);
		return (0);
	}

	degrees Route::maxDownhillGradient() const
	{
		/* Returns the minimum (most negative) value of gradient between successive points
		* on the Route.
		*/
		implementation(false);
		return (0);
	}

	degrees Route::minLat() const
	{
		/* Returns the latitude of the most Southerly point on the Route.
		*/
		implementation(false);
		return (90.0);
	}

	degrees Route::maxLat() const
	{
		/* Returns the latitude of the most Northerly point on the Route.
		*/
		implementation(false);
		return (-90.0);
	}

	degrees Route::minLon() const
	{
		/* Returns the longitude of the most Westerly point on the Route.
		*/
		implementation(false);
		return (90.0);
	}

	degrees Route::maxLon() const
	{
		/* Returns the longitude of the most Easterly point on the Route.
		*/
		implementation(false);
		return (-90.0);
	}

	metres Route::minEle() const
	{
		/* Returns the elevation of the lowest point on the Route.
		*/
		implementation(false);
		return (4000);
	}

	metres Route::maxEle() const
	{
		/* Returns the elevation of the highest point on the Route.
		*/
		implementation(false);
		return (0);
	}

	unsigned int Route::timesVisited(const Position & pos) const
	{
		/* Returns the number of times that the Position is visited on the Route.
		*/
		implementation(false);
		return (0);
	}

	unsigned int Route::timesVisited(const string & nameTag) const
	{
		/* Returns the number of times that the Position with <name>nameTag</name>
		* is visited on the Route.  If nameTag == "", return 0.
		*/
		implementation(false);
		return (0);
	}

	unsigned int Route::numPositions() const
	{
		/* Returns the number of Positions in this Route.
		*/
		implementation(false);
		return (0);
	}

	string Route::nameOf(const Position & pos) const
	{
		/* Determine whether the Position occurs anywhere on the Route,
		* and if so whether it has a name at any of the occurrences;
		* return the name if it has one, or an empty string otherwise.
		*/
		implementation(false);
		return (string("not implemented"));
	}

	Position Route::positionOf(const string & nameTag) const
	{
		/* This function is the inverse of Route::nameOf().  It searches on the Route
		* for a point named nameTag.  If found, its Position is returned, else the
		* North Pole Position is returned.
		*/
		implementation(false);
		return (northPole);
	}

	const Position & Route::operator[](unsigned int idx) const
	{
		/* Provides access to the sequence of points that make up the Route.
		* Out-of-range access should return the North Pole Position.
		*/
		implementation(false);
		return (northPole);
	}

	bool Route::areSameLocation(const Position & p1, const Position & p2) const
	{
		/* Determines whether the 2 Positions parameters are less than "granularity" apart.
		*/
		implementation(true);
		return (distanceBetween(p1, p2) < granularity);
	}

	bool Route::append(const Position & pos, const string & name)
	{
		/*  Append the position to the end of the "positions" vector, unless
		*  it is close enough to the last Position to be considered the same
		*  location (see "areSameLocation()").  The routeLength is updated
		*  accordingly.
		*/
		implementation(true);
		Position prevPos = positions.back();
		if (areSameLocation(pos, prevPos))
		{
			return false;
		}
		else
		{
			metres deltaH = distanceBetween(pos, prevPos);
			metres deltaV = pos.getElevation() - prevPos.getElevation();
			routeLength += std::sqrt(std::pow(deltaH, 2) + std::pow(deltaV, 2));
			positions.push_back(pos);
			positionNames.push_back(name);

			return true;
		}
	}

	void Route::simplify(unsigned int overridingGranularity)
	{
		/* Simplify the Route by reducing the number of points: any point in
		* the Route that differs in distance from its predecessor by less than
		* the parameter is discarded.
		*/
		implementation(false);
	}

	void Route::implementation(bool implemented) const //function to check if it is implemented
	{
		assert(implemented);
	}

	bool Route::constCheck(string source, string type) //function to check if the element exists
	{
		if (!XML_Parser::elementExists(source, type))
		{
			oss << std::endl << "no" << type << " tag";
			constStat(false);
			return false;
		}
		return true;
	}

	void Route::constStat(bool stat) //function to see the status of the constructor
	{
		constructorReport = oss.str();
		constructorSucceeded = stat;
	}

	void Route::distCalc() //function to calculate the distance between pci1 and pci2
	{
		routeLength = 0;
		vector<Position>::const_iterator pci1, pci2;
		pci1 = pci2 = positions.begin();
		++pci2;
		for (; pci2 != positions.end(); ++pci1, ++pci2)
		{
			metres deltaH = distanceBetween(*pci1, *pci2);
			metres deltaV = pci1->getElevation() - pci2->getElevation();
			routeLength += std::sqrt(std::pow(deltaH, 2) + std::pow(deltaV, 2));
		}
	}

	void Route::checkFile(bool isFileName, std::string &source)
	{
		if (isFileName)
		{
			string content, line;
			std::ifstream file(source);
			if (!file)
			{
				oss << endl << "error opening constructor source file " << source;
				constStat(false); //changed
				return;
			}
			oss << endl << "source file " << source << " opened okay";
			while (file.good())
			{
				getline(file, line);
				content += '\n';
				content += line;
			}
			oss << endl << "source file " << source << " read okay";
			source = content;
		}
	}
}
