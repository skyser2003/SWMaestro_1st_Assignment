using UnityEngine;
using System.Collections;

public class PlayerController : MonoBehaviour {
    public Game game;

    private void FixedUpdate()
    {
        int x = 0;
        int y = 0;

        if (Input.GetKeyDown(KeyCode.W)) {
            y = 1;
        }
        else if (Input.GetKeyDown(KeyCode.A)) {
            x = -1;
        }
        else if (Input.GetKeyDown(KeyCode.S)) {
            y = -1;
        }
        else if (Input.GetKeyDown(KeyCode.D)) {
            x = 1;
        }

        if (x != 0 || y != 0) {
            game.Move(x, y);
        }
    }
}