using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour{
    public Camera[] cameras;
    private int cameraIndex = 0;

    void Start(){
        cameras[0].enabled = true;

        for(int i = 1; i < cameras.Length; i++){
            cameras[i].enabled = false;
        }
    }

    void Update(){
        if(Input.GetKeyDown(KeyCode.C)){
            cameras[cameraIndex].enabled = false;
            cameraIndex = (cameraIndex + 1) % cameras.Length;
            cameras[cameraIndex].enabled = true;
        }
    }
}
