/*
 * Created  by rbh, 03/10/13
 * Modified by nas, 18/12/16
 */

/*
 *  This file contains a placeholder main() function (and some auxiliary functions)
 *  to support some initial experimentation with Routes and Tracks.
 */

#include <iostream>

#include "route.h"
#include "track.h"

using namespace GPXP;

using std::cout;
using std::endl;
using std::string;

void printRouteInfo(const Route & route, bool printBuildReport)
{
    cout << "Route name: " << route.name() << endl;
    cout << "Built okay: " << (route.builtOk() ? "True" : "False" ) << endl;
    cout << "Build report: " << (printBuildReport ? route.buildReport() : "omitted") << endl;
    cout << "Total route length: " << route.totalLength() << endl;
    cout << "Net route length: " << route.netLength() << endl;
    // Other functionality not yet implemented
}

void printTrackInfo(const Track & track)
{
    // Other functionality not yet implemented
}

void gpxRouteTest(const string & filename, bool printBuildReport)
{
    Route r(filename, true);
    printRouteInfo(r, printBuildReport);
    cout << endl;
}

void gpxTrackTest(const string & filename, bool printBuildReport)
{
    Track t(filename, true);
    printRouteInfo(t, printBuildReport);
    printTrackInfo(t);
    cout << endl;
}

int main()
{
    const string gpxLogsDir = "../logs/GPX/";
    const string routesDir = gpxLogsDir + "routes/";
    const string tracksDir = gpxLogsDir + "tracks/";

    /* For P4, you will probabably want to view the build reports,
     * albeit perhaps not all of them at once.
     * To view the build report, set the boolean argument to true.
     */
    gpxRouteTest(routesDir + "ABCD.gpx", false);

    gpxRouteTest(routesDir + "NorthYorkMoors.gpx", false);

    gpxTrackTest(tracksDir + "A1B2C1D3E.gpx", false);

    return 0;
}
