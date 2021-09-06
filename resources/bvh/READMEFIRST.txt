       READMEFIRST for 3dsMax-friendly CMU BVH dataset release

 v1.04max last update May 1, 2009 by B. Hahne, hahne at io dot com
 Get the BVH data at: www.cgspeed.com in the motion capture section.

This READMEFIRST file accompanies the 3dsMax-friendly cgspeed.com "BVH
conversion" release of the Carnegie-Mellon University (CMU) Graphics
Lab Motion Capture Database.  See "Where to find stuff" at the bottom
of this file for where to get the BVH files that go with this
READMEFIRST, and/or where to get the original CMU dataset.

The CMU motion database has slightly over 2500 recorded motions in
it.  Some are quite long (thousands of frames), others are shorter.

I've also done a Motionbuilder-friendly release of this CMU BVH
dataset, however this particular READMEFIRST is for the Max-friendly
release, not the Motionbuilder-friendly release.  The two BVH releases
are completely separate -- you download them as entirely different
sets of .zip files.

The original CMU motion capture database isn't in BVH format - it's
in ASF/AMC format.  This BVH conversion release was created by Bruce
Hahne, a hobbyist animator, in the interest of making the data more
available and easily usable by other animators.  I presently (2009)
maintain the web site www.cgspeed.com, where this BVH conversion
release will be available or linked.

The emphasis on this release is to produce BVH files that can rapidly
be used in 3dStudio Max with Biped for motion retargetting.  The files
are probably not friendly for any other program that imports BVH,
since every program's character skeletons have different joint names,
hierarchies, skeleton zero-pose, and joint rotation orders.


ADVANTAGES OF THIS RELEASE OVER THE ORIGINAL CMU DATA:
- Very easy and fast to use with 3dsMax Biped.

- Joint renaming: As many joints as possible have been renamed to be
  compatible with 3dsMax's BVH import capability for Biped.

- Easy retargeting: since 3dsMax Biped allows biped-to-biped
  retargeting even across different Biped skeleton setups, it's now
  possible to use the CMU motion data with arbitrary Biped skeletons,
  at least within 3dsMax.  This is a huge win, because it means that
  you DON'T have to create a skeleton whose bone setup matches that of
  the original CMU data.

- Base pose modification: 3dsMax requires an unusual skeleton BVH
  "base pose" aka "zero pose".  For the 3dsMax-friendly release I've
  adjusted the underlying dataset to put the zero pose into the
  appropriate arms-down position.  Numerous adjustments to the
  keyframes on the arms were then required to handle the change in
  rotation axes that happens when you shift the underlying BVH zero
  pose.

- Hand-to-wrist keyframe migration: This 3dsMax-friendly BVH release
  shifts keyframes from the "hand" joints onto the "wrist" joints,
  making this data available to Max.  3dsMax BVH import doesn't
  support both "wrist" and "hand" joints, so without this datashift,
  the wrist rotations of the original capture would end up lost.

- Index files: The release includes consolidated indexes that list
  the motion filenames and their descriptions. Both spreadsheet and 
  word processor friendly index files are available.



CONVERSION PROCESS:

- I started with the full set of AMC and ASF files, available from CMU
  as a single .zip file
- I ran the AMC/ASF files through amc2bvh in batch mode to produce BVH
  files.  I haven't released these "raw" files publicly since they're
  not that exciting.  The releases I've done so far
  (Motionbuilder-friendly and Max-friendly versions) both start with
  these "raw" BVH filers and then convert them some more.

- I ran the BVH files through a Python script that I wrote
  specifically to convert to Max-friendly format.  This script does
  quite a lot of work:

  1. The script adjusts the internal zero pose of the skeleton so that
  the arms point down to the sides rather than out in a T-pose.
  3dsMax BVH import requires this very unusual zero pose.

  2. The script then adjusts the rotation keyframes on the the arms --
  starting at the clavicles and working all the way down to the
  fingers -- to adjust for the fact that the underlying skeleton
  definition has changed.

  3. The script adds the rotation keyframes from the original CMU
  "lhand" and "rhand" joints onto the existing wrist joint data, and
  zeroes out the rotation keyframes on the hands.  This is a data
  merge that forces the lwrist and rwrist joints to perform the
  rotations formerly handled both by the wrists and the hands.  This
  step is necessary because 3dsMax BVH import doesn't allow both
  "wrist" and "hand" joints -- you have to have all of the wrist
  rotations in one place.

  4. Playback speed: The CMU dataset was sampled at 120fps, however
  this information apparently isn't saved in the CMU-distributed
  AMC/ASF files, and the freeware utility amc2bvh simply assumes a
  default value of 30fps (Frame Time = .033333) when it writes out BVH
  files.  My script fixes the problem by rewriting Frame Time to
  .0083333 in each BVH file, which equates to 120fps.  Testing so far
  suggests that 3dsMax imports the BVH to conform to 30fps and is
  possibly either using only every 4th keyframe, or is averaging every
  4 keyframes together to get a 30fps result.  Whether this behavior
  is desirable or undesirable depends on what you want.  If you want
  to force Max to import ALL of the original BVH keyframes, you can
  always hand-edit the BVH file and change "Frame Time" back to 0.33333

I've done no cleanup or noise reduction to this data as part of the
conversion.  The CMU data IS sometimes noisy and can exhibit some
abrupt wrist-flips and ankle-flips, so watch out, sine occasionally you'll
need to manually clean the data in some spots.


----


INDEX/INFORMATION FILES: 

Each .zip file in this BVH conversion release should include a copy of
this READMEFIRST.txt file, plus a step-by-step help file called
HOW-TO-USE-THESE-FILES.txt, plus four variations of the same motion
index information:
- cmu-mocap-index-spreadsheet.ods: Open Document / OpenOffice
  spreadsheet format
- cmu-mocap-index-spreadsheet.xls: Microsoft Excel format
- cmu-mocap-index-txt.txt: A simple text file with the index
  information and no commentary.
- cmu-mocap-index-text.rtf: Rich Text Format index information with
  some commentary.


USAGE RIGHTS:

CMU places no restrictions on the use of the original dataset, and I
(Bruce) place no additional restrictions on the use of this particular
BVH conversion.  If you do use it for something, I'd be interested to
hear what you're using it for, so feel free to drop me an email.

Here's the relevant paragraph from mocap.cs.cmu.edu:

 Use this data!  This data is free for use in research and commercial
 projects worldwide.  If you publish results obtained using this data,
 we would appreciate it if you would send the citation to your
 published paper to jkh+mocap@cs.cmu.edu, and also would add this text
 to your acknowledgments section: "The data used in this project was
 obtained from mocap.cs.cmu.edu.  The database was created with funding
 from NSF EIA-0196217."


JOINT RENAMING TEMPLATE

Here's the joint renaming template that my unreleased Python script
uses, with some comments that come from my analysis of the skeleton.
The left column is the original joint name used by the CMU dataset,
and the right column is the joint name that my script outputs.  Most
of the time this right-column name is one that 3dsMax recognizes,
however in some cases we have to intentionally convert to a name that
Max won't recognize, because we don't want Max to use the joint.

---------------------------------------------------------------------
# Some facts about the CMU skeleton:
# lhipjoint and rhipjoint are in the same location as hip, and have no
# keyframes.
#
# lowerback is in the same location as hip, and has keyframes.
#
# thorax, lowerneck, lclavicle, and rclavicle are all in the same location.
# thorax and lowerneck are keyed. lclavicle and rclavicle are not.
#
# lwrist, lhand, and lthumb are all in the same location.
# rwrist, rhand, and rthumb are all in the same location.
#
# lwrist and rwrist have rotation keyframes along one axis only, which
# is a "twist" axis parallel to the lower arm.  The CMU dataset puts
# the more interesting wrist motions (wrist bends) into keyframes on
# lhand and rhand.
#
# Although we have two neck joints, the CMU "lowerneck" is really in
# the middle of the spine -- it sure doesn't look anywhere close to
# the human neck to me.
#
# Per CMU web page: 'The "finger" and "thumb" joints are added to the
# skeleton for editing convenience - we do not actually capture these
# joints' motions and any such data should be ignored.'


TEMPLATE: cmu

# Left column is the joint name from the original CMU dataset.
# Right column is the renaming to make the dataset Max-friendly.

hip                                     Hips

# lhipjoint has no keyframes and is just a connector to attach the
# leg.  Max doesn't want it, so we just maintain its original name and
# let Max ignore it.
 lhipjoint                              LHipJoint  # Not used by Max
  lfemur                                LeftHip
   ltibia                               LeftKnee
    lfoot                               LeftAnkle
     ltoes                              LeftToe
 rhipjoint                              RHipJoint  # Not used by Max
   rfemur                               RightHip
    rtibia                              RightKnee
     rfoot                              RightAnkle
      rtoes                             RightToe

# CMU's lowerback is in the same location as Hips.

 lowerback                              lowerback  # Want Max to ignore
  upperback                             Chest
   thorax                               Chest2

# "Lower" and "upper" neck?  Good grief.
    lowerneck                           lowerneck
     upperneck                          Neck
      head                              Head
    lclavicle                           LeftCollar      # child of thorax
     lhumerus                           LeftShoulder
      lradius                           LeftElbow

# In 3dsMax, "LeftWrist" is a synonym for "LeftHand".  You can't have
# both a "wrist" and a "hand"
       lwrist                           LeftWrist
        lhand                           lhand

# LFingers and LThumb: CMU notes that there's no data on these joints,
# so we want to ignore them.
         lfingers                       LFingers   # Want Max to ignore this.
        lthumb                          LThumb  # Want Max to ignore this.
    rclavicle                           RightCollar # child of thorax
     rhumerus                           RightShoulder
      rradius                           RightElbow
       rwrist                           RightWrist
        rhand                           rhand    # Want Max to ignore this.
         rfingers                       RFingers  # Want Max to ignore this.
        rthumb                          RThumb  # Want max to ignore this.

# END OF CMU JOINT RENAMING TEMPLATE with comments
-----------------------------------------------------------------


FUTURE PROJECT IDEAS:
- Conversion to MovieStorm, SecondLife, or iClone.
  
- Clean/smooth the data.



CONTACT INFO AND WHERE TO FIND STUFF:
 This BVH conversion release: www.cgspeed.com
 Original CMU catabase (no BVH): mocap.cs.cmu.edu
 AMC2BVH freeware utility: http://vipbase.net/amc2bvh/
 3dsMax: www.autodesk.com/3dsmax
 MotionBuilder: www.autodesk.com/motionbuilder

To contact the creator of this BVH conversion release: hahne at io dot com

If you like this BVH conversion release, feel free to drop me email
and let me know what you're doing with it.
