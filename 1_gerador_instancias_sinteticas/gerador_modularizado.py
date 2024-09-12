
def Cria_Grid(x_min, x_max, y_min, y_max, print_grid=False):
    
    import numpy as np
    import matplotlib.pyplot as plt
    from matplotlib import cm
    
    dx, dy = (1., 1.)
    grid = np.zeros(( int((y_max-y_min)/dy), int((x_max-x_min)/dx) ))
    
    if (print_grid):
        plt.pcolormesh(grid, alpha=0.5)
    
    return grid

def Cria_Bacias(x_min, x_max, y_min, y_max, nx_bacias, ny_bacias, grid, estrategias, qualidades_dado, 
                print_grid=False):
    
    import numpy as np
    import matplotlib.pyplot as plt
    from matplotlib import cm
    
    bacias = {}
    count = 0
    x_step = (x_max-x_min)/nx_bacias
    y_step = (y_max-y_min)/ny_bacias
    for i in range(1, ny_bacias+1):
        y_min_curr = (i-1)*y_step
        y_max_curr = (i)*y_step
        for j in range(1, nx_bacias+1):
            x_min_curr = (j-1)*x_step
            x_max_curr = j*x_step
            count += 1
            bacias[count] = {}
            bacias[count]['Coordenadas'] = ((x_min_curr, x_max_curr),(y_min_curr, y_max_curr))
            bacias[count]['Maturidade'] = np.random.choice(estrategias)
            bacias[count]['Qualidade do dado'] = np.random.choice(qualidades_dado)
            grid[int(x_min_curr):int(x_max_curr), int(y_min_curr):int(y_max_curr)] = count
    
    if (print_grid):
        colormap = cm.inferno
        plt.figure(figsize=(7, 7))
        plt.pcolormesh(grid, alpha=0.5, cmap=colormap)
    
    return grid, bacias, x_step, y_step


def Cria_Plays(n_plays):
    
    import copy
    from scipy import stats
    
    soterramento_range = (3000., 5000.) # (1000., 5000.)
    pcgna_range = (0., 1.)
    area_range = (100, 200.) # (20., 200.)
    netpay_range = (50., 100.) # (5., 100.)
    phi_range = (0.16, 0.32) # (0.10, 0.32)
    trapfill_range = (0.5, 1.)
    shc_range = (0.5, 1.)
    bo_range = (1.4, 1.9)
    bg_range = (0.002, 0.004)
    rgo_range = (150, 250)
    rlg_range = (0.1, 0.15)
    froleo_range = (0.2, 0.25)
    frga_range = (0.2, 0.25)
    frgna_range = (0.2, 0.25)
    frcond_range = (0.2, 0.25)
    
    plays = [i for i in range(1, n_plays+1)]
    
    plays_completo = {}
    for p in plays:
        plays_completo[copy.copy(p)] = {}

        loc, scale = soterramento_range[0], soterramento_range[1]-soterramento_range[0]
        plays_completo[copy.copy(p)]['Soterramento'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = pcgna_range[0], pcgna_range[1] - pcgna_range[0]
        plays_completo[copy.copy(p)]['pcgna'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = area_range[0], area_range[1] - area_range[0]
        plays_completo[copy.copy(p)]['area'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = netpay_range[0], netpay_range[1] - netpay_range[0]
        plays_completo[copy.copy(p)]['netpay'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = phi_range[0], phi_range[1] - phi_range[0]
        plays_completo[copy.copy(p)]['phi'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = trapfill_range[0], trapfill_range[1] - trapfill_range[0]
        plays_completo[copy.copy(p)]['trapfill'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = shc_range[0], shc_range[1] - shc_range[0]
        plays_completo[copy.copy(p)]['shc'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = bo_range[0], bo_range[1] - bo_range[0]
        plays_completo[copy.copy(p)]['bo'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = bg_range[0], bg_range[1] - bg_range[0]
        plays_completo[copy.copy(p)]['bg'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = rgo_range[0], rgo_range[1] - rgo_range[0]
        plays_completo[copy.copy(p)]['rgo'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = rlg_range[0], rlg_range[1] - rlg_range[0]
        plays_completo[copy.copy(p)]['rlg'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = froleo_range[0], froleo_range[1] - froleo_range[0]
        plays_completo[copy.copy(p)]['froleo'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = frga_range[0], frga_range[1] - frga_range[0]
        plays_completo[copy.copy(p)]['frga'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = frgna_range[0], frgna_range[1] - frgna_range[0]
        plays_completo[copy.copy(p)]['frgna'] = stats.uniform(loc, scale).rvs(2)

        loc, scale = frcond_range[0], frcond_range[1] - frcond_range[0]
        plays_completo[copy.copy(p)]['frcond'] = stats.uniform(loc, scale).rvs(2)
    
    return plays_completo


def Cria_Projetos(grid, n_projetos, bacias, x_step, y_step, plays_completo, print_grid=False):
    
    import numpy as np
    from scipy import stats
    import matplotlib.pyplot as plt
    from matplotlib import cm
    
    projetos = {}
    projetos['Coordenada x'] = []
    projetos['Coordenada y'] = []
    projetos['Bacia'] = []
    projetos['Nome'] = []
    projetos['Maturidade bacia'] = []
    projetos['Qualidade do dado'] = []
    projetos['Play'] = []

    for i in range(n_projetos):

        # primeiro, sortear uma bacia
        bacia = np.random.choice(list(bacias.keys()))

        # não permitir coordenadas nas bordas das bacias
        fator = 0.9
        x_min_curr, x_max_curr = bacias[bacia]['Coordenadas'][0]
        y_min_curr, y_max_curr = bacias[bacia]['Coordenadas'][1]

        x_proj, y_proj = (np.random.uniform(x_min_curr + x_step*(1-fator), x_max_curr - x_step*(1-fator)), 
                          np.random.uniform(y_min_curr + y_step*(1-fator), y_max_curr - y_step*(1-fator)))

        projetos['Nome'].append(i+1)
        projetos['Bacia'].append(bacia)
        projetos['Coordenada x'].append(x_proj)
        projetos['Coordenada y'].append(y_proj)
        projetos['Maturidade bacia'].append(bacias[bacia]['Maturidade'])
        projetos['Qualidade do dado'].append(bacias[bacia]['Qualidade do dado'])
        projetos['Play'].append(np.random.choice(list(plays_completo.keys())))
    
    def ComputeDist(p90_play, p10_play):
        loc, scale = p90_play, p10_play - p90_play
        p90_proj, p10_proj = sorted(stats.uniform(loc, scale).rvs(2))
        mu = (np.log(p90_proj) + np.log(p10_proj)) / 2
        sigma = (np.log(p10_proj)-mu) / 1.2815515655446
        dist = stats.lognorm(s=sigma, scale=np.exp(mu))
        return dist

    projetos['Soterramento'] = []
    projetos['pcgna'] = []
    projetos['area'] = []
    projetos['netpay'] = []
    projetos['phi'] = []
    projetos['trapfill'] = []
    projetos['shc'] = []
    projetos['bo'] = []
    projetos['bg'] = []
    projetos['rgo'] = []
    projetos['rlg'] = []
    projetos['froleo'] = []
    projetos['frga'] = []
    projetos['frgna'] = []
    projetos['frcond'] = []
    projetos['geração'] = []
    projetos['migração'] = []
    projetos['reservatório'] = []
    projetos['geometria'] = []
    projetos['retenção'] = []
    projetos['PS HC'] = []

    for k, p in enumerate(projetos['Nome']):

        play = projetos['Play'][k]

        soterr_p90_play, soterr_p10_play = sorted(plays_completo[play]['Soterramento']) # soterramento
        pcgna_p90_play, pcgna_p10_play = sorted(plays_completo[play]['pcgna']) # pcgna 
        area_p90_play, area_p10_play = sorted(plays_completo[play]['area']) # area
        netpay_p90_play, netpay_p10_play = sorted(plays_completo[play]['netpay']) # netpay 
        phi_p90_play, phi_p10_play = sorted(plays_completo[play]['phi']) # phi 
        trapfill_p90_play, trapfill_p10_play = sorted(plays_completo[play]['trapfill']) # trapfill 
        shc_p90_play, shc_p10_play = sorted(plays_completo[play]['shc']) # shc 
        bo_p90_play, bo_p10_play = sorted(plays_completo[play]['bo']) # bo 
        bg_p90_play, bg_p10_play = sorted(plays_completo[play]['bg']) # bg 
        rgo_p90_play, rgo_p10_play = sorted(plays_completo[play]['rgo']) # rgo 
        rlg_p90_play, rlg_p10_play = sorted(plays_completo[play]['rlg']) # rlg 
        froleo_p90_play, froleo_p10_play = sorted(plays_completo[play]['froleo']) # froleo 
        frga_p90_play, frga_p10_play = sorted(plays_completo[play]['frga']) # frga 
        frgna_p90_play, frgna_p10_play = sorted(plays_completo[play]['frgna']) # frgna
        frcond_p90_play, frcond_p10_play = sorted(plays_completo[play]['frcond']) # frcond

        loc, scale = soterr_p90_play, soterr_p10_play - soterr_p90_play
        soterramento = stats.uniform(loc, scale).rvs(1)[0]
        projetos['Soterramento'].append(soterramento)

        loc, scale = pcgna_p90_play, pcgna_p10_play - pcgna_p90_play
        pcgna = stats.uniform(loc, scale).rvs(1)[0]
        projetos['pcgna'].append(pcgna)

        # area
        area_dist = ComputeDist(area_p90_play, area_p10_play)
        projetos['area'].append(area_dist)
        # netpay
        netpay_dist = ComputeDist(netpay_p90_play, netpay_p10_play)
        projetos['netpay'].append(netpay_dist)
        # phi
        phi_dist = ComputeDist(phi_p90_play, phi_p10_play)
        projetos['phi'].append(phi_dist)
        # trapfill
        trapfill_dist = ComputeDist(trapfill_p90_play, trapfill_p10_play)
        projetos['trapfill'].append(trapfill_dist)
        # shc
        shc_dist = ComputeDist(shc_p90_play, shc_p10_play)
        projetos['shc'].append(shc_dist)
        # bo
        bo_dist = ComputeDist(bo_p90_play, bo_p10_play)
        projetos['bo'].append(bo_dist)
        # bg
        bg_dist = ComputeDist(bg_p90_play, bg_p10_play)
        projetos['bg'].append(bg_dist)
        # rgo
        rgo_dist = ComputeDist(rgo_p90_play, rgo_p10_play)
        projetos['rgo'].append(rgo_dist)
        # rlg
        rlg_dist = ComputeDist(rlg_p90_play, rlg_p10_play)
        projetos['rlg'].append(rlg_dist)
        # froleo
        froleo_dist = ComputeDist(froleo_p90_play, froleo_p10_play)
        projetos['froleo'].append(froleo_dist)
        # frga
        frga_dist = ComputeDist(frga_p90_play, frga_p10_play)
        projetos['frga'].append(frga_dist)
        # frgna
        frgna_dist = ComputeDist(frgna_p90_play, frgna_p10_play)
        projetos['frgna'].append(frgna_dist)
        # frcond
        frcond_dist = ComputeDist(frcond_p90_play, frcond_p10_play)
        projetos['frcond'].append(frcond_dist)

        geracao = min(stats.uniform(0.5, 0.6).rvs(1)[0], 1.)
        projetos['geração'].append(geracao)
        migracao = min(stats.uniform(0.5, 0.6).rvs(1)[0], 1.)
        projetos['migração'].append(migracao)
        reservatorio = min(stats.uniform(0.5, 0.6).rvs(1)[0], 1.)
        projetos['reservatório'].append(reservatorio)
        geometria = min(stats.uniform(0.5, 0.6).rvs(1)[0], 1.)
        projetos['geometria'].append(geometria)
        retencao = min(stats.uniform(0.5, 0.6).rvs(1)[0], 1.)
        projetos['retenção'].append(retencao)
        projetos['PS HC'].append( geracao*migracao*reservatorio*geometria*retencao )
    
    if (print_grid):
        colormap = cm.inferno
        fig = plt.figure(figsize=(7, 7), frameon=False)
        im1 = plt.pcolormesh(grid, alpha=0.5, cmap=colormap)
        im2 = plt.scatter(projetos['Coordenada x'], projetos['Coordenada y'], color=(0.1, 0.8, 0.8), s=50, marker='*')
        plt.show()
    
    return projetos


def Simula_Volumes(n_projetos, projetos, iteracoes):
    
    import numpy as np
    from scipy import stats
    import matplotlib.pyplot as plt
    
    projetos['volume oleo'] = []
    projetos['volume ga'] = []
    projetos['volume gna'] = []
    projetos['volume cond'] = []
    projetos['volume condicional'] = []
    projetos['média condicional'] = []
    projetos['volume incondicional'] = []
    projetos['média incondicional'] = []
    
    for k in range(n_projetos):
        
        volume_oleo_dist = []
        volume_ga_dist = []
        volume_gna_dist = []
        volume_cond_dist = []
        volume_hc_dist = []
        volume_condicional_dist = []
        volume_incondicional_dist = []
        
        for i in range(iteracoes):

            # sortear se é uma descoberta
            descoberta = stats.uniform(0, 1).rvs(1)[0] < projetos['PS HC'][k]

            # sortear o flúido principal
            fluido = 'óleo' if stats.uniform(0, 1).rvs(1)[0] < projetos['pcgna'][k] else 'gás'

            # dado o flúido principal, calcular volumes
            area = projetos['area'][k].rvs(1)[0]
            netpay = projetos['netpay'][k].rvs(1)[0]
            phi = projetos['phi'][k].rvs(1)[0]
            trapfill = projetos['trapfill'][k].rvs(1)[0]
            shc = projetos['shc'][k].rvs(1)[0]
            bo = projetos['bo'][k].rvs(1)[0]
            bg = projetos['bg'][k].rvs(1)[0]
            rgo = projetos['rgo'][k].rvs(1)[0]
            rlg = projetos['rlg'][k].rvs(1)[0]
            froleo = projetos['froleo'][k].rvs(1)[0]
            frga = projetos['frga'][k].rvs(1)[0]
            frgna = projetos['frgna'][k].rvs(1)[0]
            frcond = projetos['frcond'][k].rvs(1)[0]

            if fluido == 'óleo':
                comum = area * netpay * phi * trapfill * shc
                volume_oleo = ((comum * froleo) / bo) / (0.159)
                volume_ga = ((comum * rgo * frga) / bo)/(1000*0.159)
                volume_hc = volume_oleo + volume_ga
                volume_oleo_dist.append(volume_oleo)
                volume_ga_dist.append(volume_ga)
            elif fluido == 'gás':
                comum = area * netpay * phi * trapfill * shc
                volume_gna = ((comum * frgna) / bg) / (1000*0.159)
                volume_cond = ((comum * rlg * frcond) / bg) / (1000*0.159)
                volume_hc = volume_gna + volume_cond
                volume_gna_dist.append(volume_gna)
                volume_cond_dist.append(volume_cond)

            volume_hc_incond = volume_hc if descoberta else 0
            volume_condicional_dist.append(volume_hc)
            volume_incondicional_dist.append(volume_hc_incond)

        projetos['volume oleo'].append(volume_oleo_dist)
        projetos['volume ga'].append(volume_ga_dist)
        projetos['volume gna'].append(volume_gna_dist)
        projetos['volume cond'].append(volume_cond_dist)
        projetos['volume condicional'].append(volume_condicional_dist)
        projetos['média condicional'].append(np.mean(volume_condicional_dist))
        projetos['volume incondicional'].append(volume_incondicional_dist)
        projetos['média incondicional'].append(np.mean(volume_incondicional_dist))
    
    return projetos


def VisualizarVA(dist):
    
    import numpy as np
    import matplotlib.pyplot as plt
    
    p10, p90 = np.percentile(dist, 10), np.percentile(dist, 90)
    
    plt.hist(dist, bins=20, cumulative=False, density=True, align='right')
    plt.axvline(p10, color='r')
    plt.axvline(p90, color='r')
    plt.xlabel('classes')
    plt.ylabel('probabilidade acumulada');


def Calibra_Economico(projetos, n_projetos):
    
    import copy
    import numpy as np
    
    def AvalEcon(vol, fixo, unit):
        vpl = - fixo + (vol * unit)
        return vpl
    
    def CalibEcon(dist, fixo, unit):
        vpl_dist = []
        for v in dist:
            vpl = AvalEcon(v, fixo, unit)
            vpl_dist.append(vpl)
        return vpl_dist
    
    projetos['VPL condicional'] = []
    projetos['VPL incondicional'] = []
    projetos['VPL condicional médio'] = []
    projetos['VPL incondicional médio'] = []
    
    for i in range(n_projetos):
        vpl_dist_cond = CalibEcon(projetos['volume condicional'][i], fixo=500, unit=5)
        vpl_dist_incond = CalibEcon(projetos['volume incondicional'][i], fixo=500, unit=5)
        projetos['VPL condicional'].append(copy.copy(vpl_dist_cond))
        projetos['VPL incondicional'].append(copy.copy(vpl_dist_incond))
        projetos['VPL condicional médio'].append(np.mean(vpl_dist_cond))
        projetos['VPL incondicional médio'].append(np.mean(vpl_dist_incond))
    
    return projetos


def Calcula_Custo_Perfura(projetos, n_projetos):
    
    def CustoPoco(soterramento, maturidade):
        unit_loc = {3: 2,
                    2: 1.5,
                    1: 1}
        unit = 20000
        custo = soterramento*unit*unit_loc[maturidade]
        return custo / 10**6
    
    projetos['Custo do poço'] = []
    for i in range(n_projetos):
        projetos['Custo do poço'].append(CustoPoco(projetos['Soterramento'][i], projetos['Maturidade bacia'][i]))
    
    return projetos


def Calcula_Tempo_Perfura(projetos, n_projetos):
    
    def TempoExecucao(soterramento, maturidade):
        unit_loc = {3: 3,
                    2: 2,
                    1: 1}
        unit = (100 / 5000)
        tempo = soterramento*unit*unit_loc[maturidade]
        return max(tempo, 28.)
    
    projetos['Tempo de execução'] = []
    for i in range(n_projetos):
        projetos['Tempo de execução'].append(int(TempoExecucao(projetos['Soterramento'][i], projetos['Maturidade bacia'][i])))
    
    return projetos


def Define_Janelas_Tempo(projetos, n_projetos, t_init, t_final):
    
    import copy
    import numpy as np
    
    duracao = list(np.linspace(0.5, 5, n_projetos//2))
    
    projetos['Início do Contrato'] = []
    projetos['Final do Contrato'] = []
    
    for i in range(n_projetos):
        inicio = np.random.randint(t_init, t_final)
        final = inicio + (12 * 4 * 7)*np.random.choice(duracao)
        final = min(final, t_final)
        projetos['Início do Contrato'].append(int(copy.copy(inicio)))
        projetos['Final do Contrato'].append(int(copy.copy(final)))
    
    return projetos


def Cria_Sondas(n_sondas, bacias):
    
    import numpy as np
    
    sondas = {}
    sondas['Coordenada x'] = []
    sondas['Coordenada y'] = []
    
    for i in range(n_sondas):
        
        # primeiro, sortear uma bacia
        bacia = np.random.choice(list(bacias.keys()))
        
        # colocar coordenadas nos extremos verticais da bacia
        x_min_curr, x_max_curr = bacias[bacia]['Coordenadas'][0]
        y_min_curr, y_max_curr = bacias[bacia]['Coordenadas'][1]
        
        x_rig, y_rig = (0.0, np.random.choice([y_min_curr, y_max_curr]))
        
        sondas['Coordenada x'].append(x_rig)
        sondas['Coordenada y'].append(y_rig)
        
    return sondas


def Converte_Periodos(t_init, t_final, delta_t, n_projetos, projetos):
    
    n_periodos = ((t_final - t_init) // delta_t)
    
    for i in range(n_projetos):
        projetos['Tempo de execução'][i] = int(projetos['Tempo de execução'][i] // delta_t)
        projetos['Início do Contrato'][i] = int(projetos['Início do Contrato'][i] // delta_t)
        projetos['Final do Contrato'][i] = int(projetos['Final do Contrato'][i] // delta_t)
    
    return projetos, n_periodos


def Calcula_Deslocamento(n_sondas, n_projetos, sondas, projetos, delta_t, n_periodos):
    
    import math
    
    desloc = []
    lag = n_sondas
    for i in range(n_projetos+n_sondas):
        desloc.append([])
        for j in range(n_projetos+n_sondas):
            if (i<n_sondas) and (j<n_sondas):
                dist = math.sqrt( (sondas['Coordenada x'][i] - sondas['Coordenada x'][j])**2 + 
                                 (sondas['Coordenada y'][i] - sondas['Coordenada y'][j])**2 )
            elif (i<n_sondas) and not(j<n_sondas):
                dist = math.sqrt( (sondas['Coordenada x'][i] - projetos['Coordenada x'][j-lag])**2 + 
                                 (sondas['Coordenada y'][i] - projetos['Coordenada y'][j-lag])**2 )
            elif not(i<n_sondas) and (j<n_sondas):
                dist = math.sqrt( (projetos['Coordenada x'][i-lag] - sondas['Coordenada x'][j])**2 + 
                                 (projetos['Coordenada y'][i-lag] - sondas['Coordenada y'][j])**2 )
            else:
                dist = math.sqrt( (projetos['Coordenada x'][i-lag] - projetos['Coordenada x'][j-lag])**2 + 
                                 (projetos['Coordenada y'][i-lag] - projetos['Coordenada y'][j-lag])**2 )

            desloc[i].append(int(dist // delta_t))
    
    #d_min = min(min(desloc))
    #d_max = max(max(desloc))
    #for i in range(n_projetos+n_sondas):
    #    for j in range(n_projetos+n_sondas):
    #        desloc[i][j] = round(((desloc[i][j] - d_min) / (d_max - d_min)) * (n_periodos // 10), 0)
    
    return desloc


def Codifica_Categoricas(n_projetos, projetos, 
                         atributos,
                         lista_atributos):
    
    colunas_OHE = []
    
    for k, atributo in enumerate(atributos):
        
        unique = lista_atributos[k]
        
        for cat in unique:
            
            projetos[atributo + str(cat)] = []
            
            colunas_OHE.append(atributo + str(cat))
            
            for i in range(n_projetos):
                
                if (projetos[atributo][i] == cat):
                    projetos[atributo + str(cat)].append(1)
                else:
                    projetos[atributo + str(cat)].append(0)
    
    return projetos, colunas_OHE


def Exporta_Instancia(projetos, sondas, n_projetos, n_sondas, t_init, t_final, delta_t, n_periodos, desloc, 
                      colunas_OHE):
    
    import numpy as np
    
    colunas_out_proj = ['Coordenada x', 'Coordenada y', 'Bacia', 'Nome', 'Maturidade bacia',
                   'Qualidade do dado', 'Play', 'Soterramento', 'pcgna', 'geração', 'migração', 
                   'reservatório', 'geometria', 'retenção', 'PS HC', 'média condicional', 'média incondicional', 
                   'VPL condicional médio', 'VPL incondicional médio', 'Custo do poço', 
                   'Tempo de execução', 'Início do Contrato', 'Final do Contrato'] # + colunas_OHE
    
    for col in colunas_out_proj:
        for i, it in enumerate(projetos[col]):
            projetos[col][i] = round(projetos[col][i], 2)
    
    colunas_out_sondas = ['Coordenada x', 'Coordenada y']
    
    for col in colunas_out_sondas:
        for i, it in enumerate(sondas[col]):
            sondas[col][i] = round(sondas[col][i], 2)
    
    with open( str(n_projetos) + 'p_' + str(n_sondas) + 's_' + str(delta_t) +'dt' + '.dat', 'w') as f:
        
        # DADOS GERAIS
        print (n_projetos, round(sum(projetos['Custo do poço'])/np.random.choice([1.5, 2, 2.5]), 2), t_init, t_final, delta_t, n_periodos, file=f)
        
        # DADOS DE PROJETOS
        for col in colunas_out_proj:
            for i, it in enumerate(projetos[col]):
                print (projetos[col][i], file=f, end=" ")
            print (file=f)
        
        print (n_sondas, file=f)
        
        # DADOS DE SONDAS
        for col in colunas_out_sondas:
            for i, it in enumerate(sondas[col]):
                print (sondas[col][i], file=f, end=" ")
            print (file=f)
        
        # DADOS DE DESLOCAMENTOS
        for i in range(n_projetos + n_sondas):
            for j in range(n_projetos + n_sondas):
                print (desloc[i][j], file=f, end=" ")
            print(file=f)



def Gerar_Instancia(x_min, x_max, y_min, y_max, 
                    nx_bacias, ny_bacias,
                    n_plays, n_projetos, n_sondas, iteracoes,
                    t_init, t_final, delta_t,
                    estrategias, qualidades_dado,
                    print_grid = False):
    
    atributos = ['Maturidade bacia', 'Qualidade do dado', 'Play']
    
    grid = Cria_Grid(x_min, x_max, y_min, y_max, print_grid)
    
    grid, bacias, x_step, y_step = Cria_Bacias(x_min, x_max, y_min, y_max, nx_bacias, ny_bacias, grid, 
                                               estrategias, qualidades_dado, print_grid)
    
    plays_completo = Cria_Plays(n_plays)
    
    projetos = Cria_Projetos(grid, n_projetos, bacias, x_step, y_step, plays_completo, print_grid)
    
    projetos = Simula_Volumes(n_projetos, projetos, iteracoes)
    
    projetos = Calibra_Economico(projetos, n_projetos)
    
    projetos = Calcula_Custo_Perfura(projetos, n_projetos)
    
    projetos = Calcula_Tempo_Perfura(projetos, n_projetos)
    
    projetos = Define_Janelas_Tempo(projetos, n_projetos, t_init, t_final)
    
    projetos, n_periodos = Converte_Periodos(t_init, t_final, delta_t, n_projetos, projetos)
    
    sondas = Cria_Sondas(n_sondas, bacias)
    
    desloc = Calcula_Deslocamento(n_sondas, n_projetos, sondas, projetos, delta_t, n_periodos)
    
    lista_atributos = [estrategias, qualidades_dado, list(plays_completo.keys())]
    
    projetos, colunas_OHE = Codifica_Categoricas(n_projetos, projetos, atributos, lista_atributos)
    
    Exporta_Instancia(projetos, sondas, n_projetos, n_sondas, t_init, t_final, delta_t, n_periodos, desloc, 
                      colunas_OHE)


def Gerar_Instancias_Batch(n_projetos=[10, 20], n_sondas=[2, 5], delta_t=[1*7*4, 1*7]):
    
    x_min, x_max = (0., 100.)
    y_min, y_max = (0., 100.)
    nx_bacias = 9
    ny_bacias = 1
    n_plays = 10
    iteracoes = 250
    t_init = 0
    t_final = 5*12*4*7
    estrategias = [1, 2, 3]
    qualidades_dado = [1, 2, 3]
    
    total = len(n_projetos) * len(n_sondas) * len(delta_t)
    i = 0
    
    for n_p in n_projetos:
        for n_s in n_sondas:
            for dt in delta_t:
                
                i += 1
                print ("Gerando instância ", i, "/", total)
                
                Gerar_Instancia(x_min, x_max, y_min, y_max, 
                                nx_bacias, ny_bacias,
                                n_plays, n_p, n_s, iteracoes,
                                t_init, t_final, dt, 
                                estrategias, qualidades_dado, 
                                print_grid=False)


def main():

    n_projetos = [10, 40, 70, 100, 130, 160, 200, 220, 250, 270] # [10, 40, 70, 100, 130, 160, 200, 220, 250, 270]
    n_sondas = [2, 5, 10] # [2, 5, 10]
    delta_t = [1*7*2, 1*7, 1] # [1*7*4, 1*7*2, 1*7, 1]
    Gerar_Instancias_Batch(n_projetos, n_sondas, delta_t)


if (__name__ == "__main__"):
    main()

