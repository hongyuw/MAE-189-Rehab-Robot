using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
public class Grab : MonoBehaviour
{
    string message;

    public string[] data_s = { "", "", "", "" };
    public float xPos;
    public float yPos;
    public float zPos;
    public float pitch;
    public int xPos1;
    public int yPos1;
    public int zPos1;
    public int pitch1;
    

    private float ytemp = 15, ztemp = 0;
    SerialPort sp = new SerialPort("COM9", 9600);
    SerialPort sp1 = new SerialPort("COM4", 9600);
    //  public Controller Controller;
    //  public int m = 0;
    GameObject grabbedObject;
    private Vector3 offset;
    // Use this for initialization
    void Start()
    {//******************* serial read
        sp1.Open();
        sp1.ReadTimeout = 1;
        sp.Open();
        sp.ReadTimeout = 1;
        message = sp.ReadLine();
        
        data_s = message.Split(new string[] { "," }, System.StringSplitOptions.None);
        if (message.Length == 15)
        {
            int.TryParse(data_s[0], out xPos1);
            int.TryParse(data_s[1], out yPos1);
            int.TryParse(data_s[2], out zPos1);
            int.TryParse(data_s[3], out pitch1);
            xPos = xPos1 - 200;
            yPos = yPos1 - 200;
            zPos = zPos1 - 200;
            pitch = pitch1;
            ytemp = yPos;
            ztemp = zPos;
        }
    }
    GameObject GetMouseHoverObject(float range)
    {
        Vector3 position = gameObject.transform.position;
        RaycastHit raycastHit;
        Vector3 target = position + Camera.main.transform.forward * range;
        if (Physics.Linecast(position, target, out raycastHit))
        {
            offset = transform.position - raycastHit.collider.gameObject.transform.position;
            return raycastHit.collider.gameObject;
        }
        return null;
    }

    void TryGrabObject(GameObject grabObject)
    {
        if (grabObject == null)
            return;
        grabbedObject = grabObject;

    }
    void DropObject()
    {
        if (grabbedObject == null)
            return;
        sp1.WriteLine("b");
        grabbedObject = null;

    }
    // Update is called once per frame
    void Update()
    {


        if (grabbedObject != null)
        {//gameObject.transform.position + Camera.main.transform.forward * 5
            if(grabbedObject.tag == "Cube1")
                sp1.WriteLine("r");
            // Debug.Log("r");
            grabbedObject.transform.position = transform.position - offset;
        }
        
           // sp1.Write("b");
           // Debug.Log("b");
        
           

        if (pitch>270)
        {
            if (grabbedObject == null)
            {
                TryGrabObject(GetMouseHoverObject(5));
                
            }
        }
        if (pitch<230)
        {
            grabbedObject = null;
            Debug.Log(grabbedObject);

        }

        //transform***********************
        if (sp.IsOpen)
        {
            try
            {

                message = sp.ReadLine();
                //Debug.Log("message " + message.Length);
                data_s = message.Split(new string[] { "," }, System.StringSplitOptions.None);



            }
            catch (System.Exception)
            {
            }
            if(message.Length == 15)
            {
                int.TryParse(data_s[0], out xPos1);
                int.TryParse(data_s[1], out yPos1);
                int.TryParse(data_s[2], out zPos1);
                int.TryParse(data_s[3], out pitch1);
                xPos = xPos1 - 200;
                yPos = yPos1 - 200;
                zPos = zPos1 - 200;
                pitch = pitch1;
                ytemp = yPos;
                ztemp = zPos;
                if (true)//Mathf.Abs(ytemp - yPos) < 20 && Mathf.Abs(ztemp - zPos) < 20
                {

                  //  Debug.Log(yPos + " and " + zPos + " pitch " + pitch);
                    ytemp = yPos;
                    ztemp = zPos;

                    transform.position = new Vector3(yPos-600,zPos-50,-xPos+50 );
                    //if (xPos > 50 && yPos > 20)
                    //   sp.Write("r");
                    //else
                    //   sp.Write("a");
                }

            }


        }
        
    }
}
