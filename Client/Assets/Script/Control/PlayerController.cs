﻿using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class PlayerController : MonoBehaviour {
    public Game game;
    public Canvas gameCanvas;
    public Canvas endCanvas;
    public Canvas scoreCanvas;

    private Text scoreText;
    private Text nameText;
    private int score;

    private void Start()
    {
        var scoreUI = endCanvas.transform.Find("Text_score");
        var nameUI = endCanvas.transform.Find("InputField_name/Text");
        scoreText = scoreUI.GetComponent<Text>();
        nameText = nameUI.GetComponent<Text>();

        StartGame();
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

            if (game.IsGameEnd() == false) {
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

    private void ProcessGameEnd()
    {
        Debug.Log("Game end");
        game.Field.SetActive(false);
        gameCanvas.gameObject.SetActive(false);
        endCanvas.gameObject.SetActive(true);

        score = 100;
        scoreText.text = score.ToString();
    }

    public void StartGame()
    {
        endCanvas.gameObject.SetActive(false);
        scoreCanvas.gameObject.SetActive(false);
        gameCanvas.gameObject.SetActive(true);

        game.InitLogic();
    }

    public void OnScoreSubmit()
    {
        var netClient = GetComponent<NetworkClient>();
        netClient.SendHighScorePacket(nameText.text, score);
    }

    public void ShowScore(List<string> nameList, List<int> scoreList)
    {
        gameCanvas.gameObject.SetActive(false);
        endCanvas.gameObject.SetActive(false);
        scoreCanvas.gameObject.SetActive(true);

        Debug.Log(nameList.Count);

        for (int i = 0; i < nameList.Count || i < 5; ++i) {
            string name = "";
            string score = "";

            if (i < nameList.Count) {
                name = nameList[i];
                score = scoreList[i].ToString();
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