#pragma once

#include <mc_rbdyn/RobotModule.h>
#include <mc_rtc/logging.h>

#include <mc_rbdyn_urdf/urdf.h>

#include <mc_robots/api.h>

namespace mc_robots
{

  struct MC_ROBOTS_DLLAPI HumanRobotModule : public mc_rbdyn::RobotModule
  {
  public:
    HumanRobotModule();

  protected:
    std::map<std::string, std::pair<std::string, std::string>> getConvexHull(
        const std::map<std::string, std::pair<std::string, std::string>> & files) const;

    void readUrdf(const std::string & robotName, bool fixed, const std::vector<std::string> & filteredLinks);

    std::map<std::string, std::vector<double>> halfSittingPose(const rbd::MultiBody & mb) const;

    std::vector<std::map<std::string, std::vector<double>>> nominalBounds(const mc_rbdyn_urdf::Limits & limits) const;

    std::map<std::string, std::pair<std::string, std::string>> stdCollisionsFiles(const rbd::MultiBody & mb) const;

  public:
    std::vector<std::string> virtualLinks;
    std::vector<std::string> gripperLinks;
    std::map<std::string, std::vector<double>> halfSitting;
    mc_rbdyn_urdf::Limits limits;
    std::vector<std::string> filteredLinks;
  };

} // namespace mc_robots

extern "C"
{
  ROBOT_MODULE_API std::vector<std::string> MC_RTC_ROBOT_MODULE() { return {"human"}; }
  ROBOT_MODULE_API void destroy(mc_rbdyn::RobotModule * ptr) { delete ptr; }
  ROBOT_MODULE_API mc_rbdyn::RobotModule * create(const std::string & robot)
  {
    if(robot == "human")
    {
      LOG_INFO("HUMAN module crated")
      return new mc_robots::HumanRobotModule();
    }
    else
    {
      LOG_ERROR_AND_THROW(std::runtime_error, "Attempted to load " << robot << " from human module")
    }
  }
}
