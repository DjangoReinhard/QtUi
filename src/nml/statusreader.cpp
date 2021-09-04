#include <stat_msg.hh>
#include <cmd_msg.hh>
#include <emc_nml.hh>
#include <insulatePose.h>
#include <statusreader.h>
#include <positioncalculator.h>
#include <gcodeinfo.h>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <cmath>


/*
 * /usr/bin/ld: statusreader.o: in function `StatusReader::StatusReader(PositionCalculator&, GCodeInfo&)':
 * /d/PUBLIC/build-QtUi-Desktop_5_15_opt-Debug/../QtUi/src/nml/statusreader.cpp:21:
 *          undefined reference to `NML::operator new(unsigned long)'
 * /usr/bin/ld: /d/PUBLIC/build-QtUi-Desktop_5_15_opt-Debug/../QtUi/src/nml/statusreader.cpp:21:
 *          undefined reference to `emcFormat(int, void*, CMS*)'
 * /usr/bin/ld: /d/PUBLIC/build-QtUi-Desktop_5_15_opt-Debug/../QtUi/src/nml/statusreader.cpp:21:
 *          undefined reference to `RCS_STAT_CHANNEL::RCS_STAT_CHANNEL(int (*)(int, void*, CMS*), char const*, char const*, char const*, int)'
 * /usr/bin/ld: /d/PUBLIC/build-QtUi-Desktop_5_15_opt-Debug/../QtUi/src/nml/statusreader.cpp:22:
 *          undefined reference to `NML::valid()'
 * /usr/bin/ld: /d/PUBLIC/build-QtUi-Desktop_5_15_opt-Debug/../QtUi/src/nml/statusreader.cpp:21:
 *          undefined reference to `NML::operator delete(void*)'
 *
 * /usr/bin/ld: statusreader.o: in function `StatusReader::update()':
 * /d/PUBLIC/build-QtUi-Desktop_5_15_opt-Debug/../QtUi/src/nml/statusreader.cpp:33:
 *          undefined reference to `NML::valid()'
 * /usr/bin/ld: /d/PUBLIC/build-QtUi-Desktop_5_15_opt-Debug/../QtUi/src/nml/statusreader.cpp:35:
 *          undefined reference to `NML::peek()'
 *
 * /usr/bin/ld: statusreader.o: in function `RCS_STAT_CHANNEL::get_address()':
 * /d/PUBLIC/build-QtUi-Desktop_5_15_opt-Debug/../QtUi/lc/include/stat_msg.hh:41:
 *          undefined reference to `NML::get_address()'
 */
StatusReader::StatusReader(PositionCalculator& posCalc, GCodeInfo& gcodeInfo)
 : QObject(0)
 , cStatus(nullptr)
 , status(nullptr)
 , pc(posCalc)
 , gi(gcodeInfo) {
#ifdef NOT_YET
  cStatus = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", EMC2_DEFAULT_NMLFILE);
  if (!cStatus || !cStatus->valid()) {
     delete cStatus;
     cStatus = nullptr;
     }
  else {
     status = static_cast<EMC_STAT*>(cStatus->get_address());
     }
#else
  // simulate movement
  vm.setValue("counter", 0);
#endif
  createModels();
  }

void StatusReader::createModels() {
  vm.setValue("taskMode",    0);
  vm.setValue("taskState",   0);
  vm.setValue("execState",   0);
  vm.setValue("interpState", 0);

  vm.setValue("axisMask",    0x1F);
  vm.setValue("units",       0);

  /*
  pc.update(&status->motion.traj.position
          , &status->motion.traj.actualPosition
          , &status->motion.traj.dtg
          , status->task.programUnits
          , &status->task.g5x_offset
          , &status->task.g92_offset
          , status->task.rotation_xy
          , &status->task.toolOffset);
   */
  vm.setValue("feedrate",    1);
  vm.setValue("rapidrate",   1);
  vm.setValue("maxVelocity", 2);
  vm.setValue("curVelocity", 2);
  /*
  gi.update(status->task.activeGCodes
          , status->task.activeMCodes
          , status->task.file
          , status->task.motionLine);
   */
  vm.setValue("spindle0Speed",          0);
  vm.setValue("spindle0Scale",          1);
  vm.setValue("spindle0Dir",            0);
  vm.setValue("spindle0Increasing",     false);
  vm.setValue("spindle0Enable",         true);
  vm.setValue("spindle0OverrideEnable", true);

  vm.setValue("pocketPrepared", 13);
  vm.setValue("toolInSpindle",  7);

  // signals:
  vm.setValue("enabledFeedOverride", true);
  vm.setValue("enabledAdaptiveFeed", true);

  vm.setValue("spindle0Homed",  false);

  vm.setValue("enabledJoint0", true);
  vm.setValue("enabledJoint1", true);
  vm.setValue("enabledJoint2", true);
  vm.setValue("enabledJoint3", false);
  vm.setValue("enabledJoint4", false);
  vm.setValue("enabledJoint5", false);
  vm.setValue("enabledJoint6", false);
  vm.setValue("enabledJoint7", false);
  vm.setValue("enabledJoint8", false);

  vm.setValue("homedJoint0", true);
  vm.setValue("homedJoint1", true);
  vm.setValue("homedJoint2", true);
  vm.setValue("homedJoint3", false);
  vm.setValue("homedJoint4", false);
  vm.setValue("homedJoint5", false);
  vm.setValue("homedJoint6", false);
  vm.setValue("homedJoint7", false);
  vm.setValue("homedJoint8", false);

  vm.setValue("coolMist",  false);
  vm.setValue("coolFlood", false);
  vm.setValue("estop",     false);
  }

void StatusReader::update() {
#ifdef NOT_YET
  if (!cStatus || !cStatus->valid()) return;
  std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
#endif
#ifndef NOT_YET
  // simulate movement
  double v = vm.getValue("counter").toDouble() + 0.001;

  vm.setValue("counter", v);
  vm.setValue("relX", 2000 * sin(v));
  vm.setValue("relY", 2000 * cos(v));
  vm.setValue("absX", 2000 * sin(v));
  vm.setValue("absY", 2000 * cos(v));
#else
  cStatus->peek();
  vm.setValue("taskMode",    status->task.mode);
  vm.setValue("taskState",   status->task.state);
  vm.setValue("execState",   status->task.execState);
  vm.setValue("interpState", status->task.interpState);

  vm.setValue("axisMask",    status->motion.traj.axis_mask);
  vm.setValue("units",       status->task.programUnits);

  pc.update(&status->motion.traj.position
          , &status->motion.traj.actualPosition
          , &status->motion.traj.dtg
          , status->task.programUnits
          , &status->task.g5x_offset
          , &status->task.g92_offset
          , status->task.rotation_xy
          , &status->task.toolOffset);

  vm.setValue("feedrate",    status->motion.traj.scale);
  vm.setValue("rapidrate",   status->motion.traj.rapid_scale);
  vm.setValue("maxVelocity", status->motion.traj.maxVelocity);
  vm.setValue("curVelocity", status->motion.traj.current_vel);

  gi.update(status->task.activeGCodes
          , status->task.activeMCodes
          , status->task.file
          , status->task.motionLine);

  vm.setValue("spindle0Speed",          status->motion.spindle[0].speed);
  vm.setValue("spindle0Scale",          status->motion.spindle[0].spindle_scale);
  vm.setValue("spindle0Dir",            status->motion.spindle[0].direction);
  vm.setValue("spindle0Increasing",     status->motion.spindle[0].increasing);
  vm.setValue("spindle0Enable",         status->motion.spindle[0].enabled);
  vm.setValue("spindle0OverrideEnable", status->motion.spindle[0].spindle_override_enabled);

  vm.setValue("pocketPrepared", status->io.tool.pocketPrepped);
  vm.setValue("toolInSpindle",  status->io.tool.toolInSpindle);

  // signals:
  vm.setValue("enabledFeedOverride", status->motion.traj.feed_override_enabled);
  vm.setValue("enabledAdaptiveFeed", status->motion.traj.adaptive_feed_enabled);

  vm.setValue("spindle0Homed",  status->motion.spindle[0].homed);

  vm.setValue("enabledJoint0", status->motion.joint[0].enabled);
  vm.setValue("enabledJoint1", status->motion.joint[1].enabled);
  vm.setValue("enabledJoint2", status->motion.joint[2].enabled);
  vm.setValue("enabledJoint3", status->motion.joint[3].enabled);
  vm.setValue("enabledJoint4", status->motion.joint[4].enabled);
  vm.setValue("enabledJoint5", status->motion.joint[5].enabled);
  vm.setValue("enabledJoint6", status->motion.joint[6].enabled);
  vm.setValue("enabledJoint7", status->motion.joint[7].enabled);
  vm.setValue("enabledJoint8", status->motion.joint[8].enabled);

  vm.setValue("homedJoint0", status->motion.joint[0].homed ? true : false);
  vm.setValue("homedJoint1", status->motion.joint[1].homed ? true : false);
  vm.setValue("homedJoint2", status->motion.joint[2].homed ? true : false);
  vm.setValue("homedJoint3", status->motion.joint[3].homed ? true : false);
  vm.setValue("homedJoint4", status->motion.joint[4].homed ? true : false);
  vm.setValue("homedJoint5", status->motion.joint[5].homed ? true : false);
  vm.setValue("homedJoint6", status->motion.joint[6].homed ? true : false);
  vm.setValue("homedJoint7", status->motion.joint[7].homed ? true : false);
  vm.setValue("homedJoint8", status->motion.joint[8].homed ? true : false);

  vm.setValue("coolMist",  status->io.coolant.mist);
  vm.setValue("coolFlood", status->io.coolant.flood);
  vm.setValue("estop",     status->io.aux.estop);

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

  std::cerr << "update took " << time_span.count() << " seconds" << std::endl;
#endif
  }