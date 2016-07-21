using System.Collections.Generic;
using UnityEngine;

public partial class NetworkClient {
    private void OnPacketReceive(PKS.SC_HIGH_SCORE_LIST pks)
    {
        var nameList = new List<string>();
        var scoreList = new List<int>();

        for (int i = 0; i < pks.name.Count; ++i) {
            var name = pks.name[i];
            var score = pks.score[i];

            nameList.Add(name);
            scoreList.Add(score);
        }

        GetComponent<PlayerController>().ShowScore(nameList, scoreList);
    }
}