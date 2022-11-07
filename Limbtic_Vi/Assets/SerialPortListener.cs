using UnityEngine;
using System.IO.Ports;

public class SerialPortListener : MonoBehaviour{
    public ArmController rightHandController;

    void OnMessageArrived(string msg){
        int[] readings = System.Array.ConvertAll(msg.Split(';'), int.Parse);

        //---Thumb (2 joints per finger)---
        double thumbJoint1Delta = 30.0 * readings[0] / 4095.0;
        double thumbJoint1Angle = thumbJoint1Delta / 23.0;

        rightHandController.rotateJoint(0, 0, Mathf.Rad2Deg * (float)thumbJoint1Angle);

        double thumbJoint2Delta = (30.0 * readings[1] / 4095.0) - thumbJoint1Delta;
        double thumbJoint2Angle = thumbJoint2Delta / 16.0;
        rightHandController.rotateJoint(0, 1, Mathf.Rad2Deg * (float)thumbJoint2Angle);
        //------

        //Rest of fingers (3 joints per finger)
        for(int i = 1; i < 5; i++){
            double joint1Delta = 30.0 * readings[i * 2] / 4095.0;
            double joint1Angle = joint1Delta / 17.0;

            rightHandController.rotateJoint(i, 0, Mathf.Rad2Deg * (float)joint1Angle);

            double joint2Delta = (30.0 * readings[i * 2 + 1] / 4095.0) - joint1Delta;
            double joint2Angle = joint2Delta / 12.0;
            rightHandController.rotateJoint(i, 1, Mathf.Rad2Deg * (float)joint2Angle);

            //interpolating based on joint2 readings
            double joint3Angle = 0.006 * joint2Angle * joint2Angle + 0.674 * joint2Angle + 0.104;
            rightHandController.rotateJoint(i, 2, Mathf.Rad2Deg * (float)joint3Angle);
        }
    }

    void OnConnectionEvent(bool success){

    }
}
