using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using GooglePlayGames;

public class PlayerController : MonoBehaviour {
    public Game game;

    public Canvas startCanvas;
    public Canvas gameCanvas;
    public Canvas endCanvas;
    public Canvas scoreCanvas;

    private Text scoreText;
    private InputField nameText;
    private int score;

    private void Start()
    {
        var scoreUI = endCanvas.transform.Find("Text_score");
        var nameUI = endCanvas.transform.Find("InputField_name");

        scoreText = scoreUI.GetComponent<Text>();
        nameText = nameUI.GetComponent<InputField>();

        // Canvas
        endCanvas.gameObject.SetActive(false);
        scoreCanvas.gameObject.SetActive(false);
        gameCanvas.gameObject.SetActive(false);
        startCanvas.gameObject.SetActive(true);

        // Google login
        PlayGamesPlatform.Activate();
        Social.localUser.Authenticate((bool success) => {
            if (success == true) {
                nameText.text = Social.localUser.userName;
                nameText.enabled = false;

                Debug.Log("Google login success : " + Social.localUser.userName);

                Social.ReportProgress("CgkIsIDW_8IYEAIQAA", 100.0f, (bool success2) => {
                    // handle success or failure
                });
            }
            else {
                nameText.text = "Failed";
                Debug.Log("Google login failed");
            }
        });
    }

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

        ProcessTurn(x, y);
    }

    private void ProcessTurn(int x, int y)
    {
        if (x == 0 && y == 0) {
            return;
        }

        bool changed = game.Move(x, y);
        if (changed == true) {
            game.AddRandom();
            game.RefreshView();

            if (game.IsGameEnd() == true) {
                ProcessGameEnd();
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

    public void ProcessGameEnd()
    {
        Social.ReportProgress("CgkIsIDW_8IYEAIQAQ", 100.0f, (bool success2) => {
            // handle success or failure
        });

        Debug.Log("Game end");
        game.Field.SetActive(false);
        gameCanvas.gameObject.SetActive(false);
        startCanvas.gameObject.SetActive(false);
        endCanvas.gameObject.SetActive(true);

        score = 100;
        scoreText.text = score.ToString() + " pt";
    }

    public void Restart()
    {
        Social.ReportProgress("CgkIsIDW_8IYEAIQAw", 100.0f, (bool success2) => {
            // handle success or failure
        });

        StartGame();
    }

    public void StartGame()
    {
        Social.ReportProgress("CgkIsIDW_8IYEAIQAg", 100.0f, (bool success2) => {
            // handle success or failure
        });

        startCanvas.gameObject.SetActive(false);
        endCanvas.gameObject.SetActive(false);
        scoreCanvas.gameObject.SetActive(false);
        gameCanvas.gameObject.SetActive(true);

        game.StartGame();
    }

    public void OnScoreSubmit()
    {
        var netClient = GetComponent<NetworkClient>();
        netClient.SendHighScorePacket(nameText.text, score);
    }

    public void ShowScore(List<string> nameList, List<int> scoreList)
    {
        Social.ReportProgress("CgkIsIDW_8IYEAIQBA", 100.0f, (bool success2) => {
            // handle success or failure
        });

        gameCanvas.gameObject.SetActive(false);
        endCanvas.gameObject.SetActive(false);
        scoreCanvas.gameObject.SetActive(true);

        for (int i = 0; i < 5; ++i) {
            string name = "";
            string score = "";

            if (i < nameList.Count) {
                name = (i + 1) + ". " + nameList[i];
                score = scoreList[i].ToString() + " pt";
            }

            var nameUI = scoreCanvas.transform.Find("name" + (i + 1)).gameObject.GetComponent<Text>();
            var scoreUI = scoreCanvas.transform.Find("score" + (i + 1)).gameObject.GetComponent<Text>();

            nameUI.text = name;
            scoreUI.text = score;
        }
    }

    public void MoveLeft()
    {
        ProcessTurn(-1, 0);
    }

    public void MoveRight()
    {
        ProcessTurn(1, 0);
    }

    public void MoveUp()
    {
        ProcessTurn(0, 1);
    }

    public void MoveDown()
    {
        game.Move(0, -1);
    }

    public void MoveLeftUp()
    {
        ProcessTurn(-1, 1);
    }

    public void MoveLeftDown()
    {
        ProcessTurn(-1, -1);
    }

    public void MoveRightUp()
    {
        ProcessTurn(1, 1);
    }

    public void MoveRightDown()
    {
        ProcessTurn(1, -1);
    }
}