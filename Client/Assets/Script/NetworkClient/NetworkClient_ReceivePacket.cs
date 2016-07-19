using UnityEngine;

public partial class NetworkClient {
    private void OnPacketReceive(PKS.SC_HIGH_SCORE_LIST pks)
    {
        for(int i = 0; i < pks.name.Count; ++i) {
            var name = pks.name[i];
            var score = pks.score[i];

            Debug.Log("name : " + name + ", score : " + score);
        }
    }
}