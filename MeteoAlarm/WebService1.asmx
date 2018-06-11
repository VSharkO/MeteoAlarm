<%@ WebService Language="C#" Class="WebService1" %>

using System.Web.Services;
using System.Xml;

[WebService(Namespace = "http://tempuri.org/")]
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
// To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
[System.Web.Script.Services.ScriptService]
public class WebService1 : System.Web.Services.WebService
{
    static string grad = "Osijek";
    string[] error = new string[1]{ "Error, cannot get data from API" };

    string baseUrl = "https://api.openweathermap.org/data/2.5/forecast?q=";
    string responderUrl = grad + ",hr&mode=xml";
    string appiKey = "&APPID=aa39e766cdddc9c64ce0fac89cbd5144";

    [WebMethod]
    public string[] returnWether()
    {
        double temperatureDouble;
        string temperature;
        string clouds;
        string windSpeed;
        string pressure;

        string[] result;

        try
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(baseUrl + responderUrl + appiKey);
            temperatureDouble = double.Parse(doc.SelectSingleNode("/weatherdata/forecast/time/temperature/@value").Value)/100 - 273.15;
            temperature = temperatureDouble.ToString();
            clouds = doc.SelectSingleNode("/weatherdata/forecast/time/clouds/@value").Value;
            windSpeed = doc.SelectSingleNode("/weatherdata/forecast/time/windSpeed/@mps").Value;
            pressure = doc.SelectSingleNode("/weatherdata/forecast/time/pressure/@value").Value;
            result = new string[4]{temperature,clouds,windSpeed,pressure};
            return result;

        }
        catch
        {
            return error;
        }

    }
}
