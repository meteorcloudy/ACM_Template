void St(){
      for (int i = 1 ; i <= N ; i++)
            dp[i][0] = d[i] ;
      for (int j = 1 ; j <= int(log(N)/log(2.0)) ; j++)
            for (int i = 1 ; i <= N-(1<<j) + 1 ; i++)
                  dp[i][j] = max(dp[i][j-1] , dp[i+(1<<(j-1))][j-1]);
}

int gt(int l ,int r){
      int k = int(log(r-l+1)/log(2.0)) ;
      return max(dp[l][k] , dp[r-(1<<k)+1][k]) ;
}
