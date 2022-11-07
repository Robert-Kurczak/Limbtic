//using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ArmController : MonoBehaviour{
    //I need a class that other than reference to gameObject
    //stores it's initial rotation values
    private class Joint{
        public Quaternion initialRotation;
        public GameObject jointObj;
        
        public Joint(GameObject obj){
            jointObj = obj;
            initialRotation = obj.transform.localRotation;
        }
    }

    //Is being set in editor
    public GameObject[] thumbJoints;
    public GameObject[] indexJoints;
    public GameObject[] middleJoints;
    public GameObject[] ringJoints;
    public GameObject[] pinkyJoints;

    private Joint[][] controlJoints = new Joint[5][];

    //Processing given in inspector GameObjects
    void Start(){
        GameObject[][] givenJoints = new GameObject[5][];

        givenJoints[0] = thumbJoints;
        givenJoints[1] = indexJoints;
        givenJoints[2] = middleJoints;
        givenJoints[3] = ringJoints;
        givenJoints[4] = pinkyJoints;

        for(int i = 0; i < 5; i++){
            Joint[] jointArr = new Joint[givenJoints[i].Length];

            for(int j = 0; j < givenJoints[i].Length; j++){
                jointArr[j] = new Joint(givenJoints[i][j]);
            }

            controlJoints[i] = jointArr;
        }
    }



    //------
    public void rotateJoint(int fingerID, int jointID, float degrees){
        Joint currentJoint = controlJoints[fingerID][jointID];

        currentJoint.jointObj.transform.localRotation = Quaternion.Euler(
            currentJoint.initialRotation.x,
            -degrees,
            currentJoint.initialRotation.z
        );
    }
}
