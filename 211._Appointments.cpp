#include <iostream> 
#include <vector> 
#include <string> 
#include <cmath> 
#include <algorithm> 
#include <unordered_set>

class Appointment
{
private:
 int startTime;
 int endTime;
 std::vector<std::string> names;

public:
 std::vector<std::string> getNames() const { return names; }

 explicit Appointment(int day, int hours, int minutes, int duration, const std::vector<std::string>& names)
 {
  startTime = (day - 1) * 24 * 60 + hours * 60 + minutes;
  endTime = startTime + duration;
  this->names = names;
 }

 bool isBooked(const Appointment& app) const
 {
  return
  (
   (app.startTime >= startTime && app.endTime <= endTime) ||
   (app.startTime <= startTime && app.endTime >= endTime) ||
   (app.startTime < startTime && app.endTime > startTime && app.endTime < endTime) ||
   (app.startTime > startTime && app.startTime < endTime && app.endTime > endTime)
  );
 }

 int getDay() const { return (startTime / (24 * 60)) + 1; }

 int getHour() const { return (startTime / 60) % 24; }

 int getMinutes() const { return startTime % 60; }

 int getDuration() const { return endTime - startTime; }
};

int main()
{
 int n;
 std::cin >> n;
 std::vector<Appointment> apps;
 bool appConflict;

 for (auto i = 0; i < n; ++i)
 {
  appConflict = false;

  std::string command;
  std::cin >> command;

  if (command == "APPOINT")
  {
   int day, duration, k;
   std::string time;
   std::cin >> day >> time >> duration >> k;

   std::vector<std::string> participants;
   for (int i = 0; i < k; ++i)
   {
    std::string name;
    std::cin >> name;
    participants.push_back(name);
   }

   Appointment app(day, std::stoi(time.substr(0, time.find(':'))), std::stoi(time.substr(time.find(':') + 1)), duration, participants);
   if (apps.empty())
   {
    apps.emplace_back(app);
    std::cout << "OK\n";
    continue;
   }
   else
   {
    int k;
    std::unordered_set<std::string> appNames;
    for (const auto& name : app.getNames())
    {
     appNames.insert(name);
    }
    for (k = 0; k < apps.size(); ++k)
    {
     if (apps[k].isBooked(app))
     {
      for (const auto& name : apps[k].getNames())
      {
       if (appNames.contains(name))
       {
        appNames.erase(name);
        appConflict = true;
       }
      }
     }
    }
    if (appConflict)
    {
     std::cout << "FAIL\n";
     for (const auto& name : app.getNames())
     {
      if (!appNames.contains(name))
      {
       std::cout << name << ' ';
      }
     }
     std::cout << "\n";
    }
    else
    {
     apps.push_back(app);
     std::cout << "OK\n";
    }
   }
  }
  else if (command == "PRINT")
  {
   int day;
   std::string name;
   std::cin >> day >> name;

   std::sort(apps.begin(), apps.end(), [](const Appointment& a, const Appointment& b) {
    if (a.getDay() != b.getDay())
     return a.getDay() < b.getDay();
    if (a.getHour() != b.getHour())
     return a.getHour() < b.getHour();
    return a.getMinutes() < b.getMinutes();
    });

   for (auto k = 0; k < apps.size(); ++k)
   {
    const auto appsKNames = apps[k].getNames();
    if (apps[k].getDay() == day && (std::find(appsKNames.begin(), appsKNames.end(), name) != appsKNames.end()))
    {
     std::cout << (apps[k].getHour() >= 10 ? std::to_string(apps[k].getHour()) : "0" + std::to_string(apps[k].getHour()))
      << ":"
      << (apps[k].getMinutes() >= 10 ? std::to_string(apps[k].getMinutes()) : "0" + std::to_string(apps[k].getMinutes()))
      << ' ' << apps[k].getDuration() << ' ';
     for (const auto& participant : appsKNames)
      std::cout << participant << ' ';

     std::cout << "\n";
    }
   }
  }
 }

 return 0;
}