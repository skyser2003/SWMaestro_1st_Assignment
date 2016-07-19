using UnityEngine;
using System.Collections;

public class PlayerController : MonoBehaviour {
    public Game game;
    public Canvas canvas;

    private void Update()
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
        else if (Input.GetKeyDown(KeyCode.Q)) {
            x = -1;
            y = 1;
        }
        else if (Input.GetKeyDown(KeyCode.E)) {
            x = 1;
            y = 1;
        }
        else if (Input.GetKeyDown(KeyCode.Z)) {
            x = -1;
            y = -1;
        }
        else if (Input.GetKeyDown(KeyCode.C)) {
            x = 1;
            y = -1;
        }

        if (x != 0 || y != 0) {
            bool changed = game.Move(x, y);
            if (changed == true) {
                game.AddRandom();
                game.RefreshView();

                if (game.IsGameEnd() == true) {
                    canvas.gameObject.SetActive(true);
                    Debug.Log("Game over");
                }
                else {
                    Debug.Log("Moved");
                }
            }
            else {
                Debug.Log("No merge");
                // Do nothing
            }
        }
    }
}